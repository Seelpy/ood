#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "./../IO/IOutputDataStream.h"
#include "./../IO/IInputDataStream.h"
#include "./../IO/Streams/CFileInputStream.h"
#include "./../IO/Streams/CFileOutputStream.h"
#include "./../IO/Modifications/DecompressDecorator.h"
#include "./../IO/Modifications/CompressDecorator.h"
#include "./../IO/Modifications/DecryptDecorator.h"
#include "./../IO/Modifications/EnctyptDecorator.h"
#include "./../IO/Modifications/CInputDataStreamDecorator.h"
#include <tuple>

const std::string OPTIONS_PREFIX = "--";

struct CommandSettings {
    std::vector<int> encryptKeys;
    std::vector<int> decryptKeys;
    bool needUseCompress = false;
    bool needUseDecompress = false;
    std::string inputFileName;
    std::string outputFileName;
};

IInputStreamPtr CreateInWithDecorators(const CommandSettings& settings)
{
    IInputStreamPtr in = std::make_unique<CFileInputStream>(settings.inputFileName);

    if (settings.needUseDecompress)
    {
        in = std::make_unique<DecompressDecorator>(std::move(in));
    }

    for (auto key : settings.decryptKeys)
    {
        in = std::make_unique<DecryptDecorator>(std::move(in), key);
    }

    return in;
}

IOutputStreamPtr CreateOutWithDecorators(const CommandSettings& settings)
{
    IOutputStreamPtr out = std::make_unique<CFileOutputStream>(settings.outputFileName);

    if (settings.needUseCompress)
    {
        out = std::make_unique<CompressDecorator>(std::move(out));
    }

    for (auto key : settings.encryptKeys)
    {
        out = std::make_unique<EncryptDecorator>(std::move(out), key);
    }

    return out;
}

std::tuple<IInputStreamPtr, IOutputStreamPtr> CreateStreams(const CommandSettings& settings)
{
    return {CreateInWithDecorators(settings), CreateOutWithDecorators(settings)};
}

bool IsOption(const std::string &commandPart)
{
    return commandPart.compare(0, OPTIONS_PREFIX.length(), OPTIONS_PREFIX) == 0;
}

CommandSettings ParseCommandSettings(const std::vector<std::string> &command)
{
    CommandSettings options;

    for (size_t i = 0; i < command.size(); ++i) {
        const auto &commandPart = command[i];

        if (IsOption(commandPart)) {
            if (commandPart == "--encrypt" || commandPart == "--decrypt") {
                if (i + 1 < command.size()) {
                    if (commandPart == "--encrypt")
                        options.encryptKeys.push_back(std::stoi(command[++i]));
                    if (commandPart == "--decrypt")
                        options.decryptKeys.push_back(std::stoi(command[++i]));
                } else
                    throw std::invalid_argument("Missing value for --encrypt option");
            }
            if (commandPart == "--compress")
                options.needUseCompress = true;
            if (commandPart == "--decompress")
                options.needUseDecompress = true;
        } else {
            if (options.inputFileName.empty())
                options.inputFileName = commandPart;
            else if (options.outputFileName.empty())
                options.outputFileName = commandPart;
        }
    }
    return options;
}

void HandleCommand(const std::vector<std::string>& command)
{
    auto settings = ParseCommandSettings(command);
    auto [in, out] = CreateStreams(settings);

    while (!in->IsEOF())
    {
        auto byte = in->ReadByte();
        out->WriteByte(byte);
    }
    out->Close();
}