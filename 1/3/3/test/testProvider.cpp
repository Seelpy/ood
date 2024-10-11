#include <gtest/gtest.h>
#include <istream>
#include "./../lib/IO/Streams/CMemoryInputStream.h"
#include "./../lib/IO/Streams/CMemoryOutputStream.h"
#include "./../lib/IO/Modifications/CompressDecorator.h"
#include "./../lib/IO/Modifications/DecompressDecorator.h"
#include "./../lib/IO/Modifications/EnctyptDecorator.h"
#include "./../lib/IO/Modifications/DecryptDecorator.h"

TEST(io, test_without_modifications)
{
    std::vector<uint8_t> inputData = {1, 2, 3, 4, 5};
    std::vector<uint8_t> outputData = {};

    CMemoryInputStream inStream(inputData);
    CMemoryOutputStream outStream(outputData);

    while (!inStream.IsEOF())
    {
        auto c = inStream.ReadByte();
        outStream.WriteByte(c);
    }

    ASSERT_EQ(inputData, outputData);
}

TEST(output_modifications, test_with_compress)
{
    std::vector<uint8_t> inData = {1, 2, 2, 3, 3, 3};
    std::vector<uint8_t> outData = {};
    IOutputStreamPtr out = std::make_unique<CMemoryOutputStream>(outData);
    out = std::make_unique<CompressDecorator>(std::move(out));

    for (auto v : inData)
    {
        out->WriteByte(v);
    }

    out->Close();

    std::vector<uint8_t> expect = {1, 1, 2, 2, 3, 3};
    ASSERT_EQ(outData, expect);
}

TEST(output_modifications, test_with_encrypt)
{
    uint32_t key = 11;
    std::vector<uint8_t> inData = {1, 2, 3, 4, 5};
    std::vector<uint8_t> outData = {};
    IOutputStreamPtr out = std::make_unique<CMemoryOutputStream>(outData);
    out = std::make_unique<EncryptDecorator>(std::move(out), key);

    for (auto v: inData)
    {
        out->WriteByte(v);
    }

    out->Close();

    auto table = GenerateSubstitutionTable(key);

    std::vector<uint8_t> expect = {table[1], table[2], table[3], table[4], table[5]};
    ASSERT_EQ(outData, expect);
}

TEST(input_modifications, test_with_decompress)
{
    std::vector<uint8_t> inData = {1, 1, 2, 2, 3, 3};
    std::vector<uint8_t> outData = {};
    IInputStreamPtr in = std::make_unique<CMemoryInputStream>(inData);
    in = std::make_unique<DecompressDecorator>(std::move(in));

    while (!in->IsEOF())
    {
        auto c = in->ReadByte();
        outData.push_back(c);
    }

    std::vector<uint8_t> expect = {1, 2, 2, 3, 3, 3};
    ASSERT_EQ(outData, expect);
}

TEST(input_modifications, test_with_decrypt)
{
    uint32_t key = 11;
    auto table = GenerateSubstitutionTable(key);
    std::vector<uint8_t> inData = {table[1], table[2], table[3], table[4], table[5]};
    std::vector<uint8_t> outData = {};
    IInputStreamPtr in = std::make_unique<CMemoryInputStream>(inData);
    in = std::make_unique<DecryptDecorator>(std::move(in), key);

    while (!in->IsEOF())
    {
        auto c = in->ReadByte();
        outData.push_back(c);
    }

    std::vector<uint8_t> expect = {1, 2, 3, 4, 5};
    ASSERT_EQ(outData, expect);
}

TEST(modifications, test_compress_with_decompress)
{
    std::vector<uint8_t> inData = {1, 1, 2, 2, 3, 3};
    std::vector<uint8_t> outData = {};

    IInputStreamPtr in = std::make_unique<CMemoryInputStream>(inData);
    IOutputStreamPtr out = std::make_unique<CMemoryOutputStream>(outData);

    in = std::make_unique<DecompressDecorator>(std::move(in));
    out = std::make_unique<CompressDecorator>(std::move(out));

    while (!in->IsEOF())
    {
        auto c = in->ReadByte();
        out->WriteByte(c);
    }

    out->Close();

    ASSERT_EQ(outData, inData);
}

TEST(modifications, test_encrypt_with_decrypt)
{
    uint32_t key = 11;
    auto table = GenerateSubstitutionTable(key);
    std::vector<uint8_t> inData = {table[1], table[2], table[3], table[4], table[5]};
    std::vector<uint8_t> outData = {};

    IInputStreamPtr in = std::make_unique<CMemoryInputStream>(inData);
    IOutputStreamPtr out = std::make_unique<CMemoryOutputStream>(outData);

    in = std::make_unique<DecryptDecorator>(std::move(in), key);
    out = std::make_unique<EncryptDecorator>(std::move(out), key);

    while (!in->IsEOF())
    {
        auto c = in->ReadByte();
        out->WriteByte(c);
    }

    ASSERT_EQ(outData, inData);
}

TEST(modifications, test_all_modifications)
{
    uint32_t key = 11;
    std::vector<uint8_t> inData = {1, 1, 2, 2, 3, 3};
    std::vector<uint8_t> outData = {};

    IInputStreamPtr in = std::make_unique<CMemoryInputStream>(inData);
    IOutputStreamPtr out = std::make_unique<CMemoryOutputStream>(outData);

    in = std::make_unique<DecryptDecorator>(std::move(in), key);
    in = std::make_unique<DecompressDecorator>(std::move(in));
    out = std::make_unique<EncryptDecorator>(std::move(out), key);
    out = std::make_unique<CompressDecorator>(std::move(out));

    while (!in->IsEOF())
    {
        auto c = in->ReadByte();
        out->WriteByte(c);
    }

    out->Close();

    ASSERT_EQ(outData, inData);
}

GTEST_API_ int main(int argc, char **argv)
{
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}