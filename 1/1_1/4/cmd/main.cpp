#include <iostream>

#include "./../lib/Handler/ShapeCommandHandler.h"
#include <string>
#include <sstream>

std::string GetHomeParams()
{
    std::ostringstream oss;
    oss << "AddShape house_body #8B4513 rectangle 50 100 100 100" << std::endl;
    oss << "AddShape roof #A52A2A triangle 50 100 150 100 100 50" << std::endl;
    oss << "AddShape door #FFD700 rectangle 90 150 20 50" << std::endl;
    oss << "DrawPicture" << std::endl;
    return oss.str();
}

std::string GetLargeStickFigureParams()
{
    std::ostringstream oss;
    oss << "AddShape head #000000 circle 100 50 40" << std::endl;
    oss << "AddShape body #000000 line 100 60 100 240" << std::endl;
    oss << "AddShape left_arm #000000 line 100 70 60 130" << std::endl;
    oss << "AddShape right_arm #000000 line 100 70 140 130" << std::endl;
    oss << "AddShape left_leg #000000 line 100 240 60 300" << std::endl;
    oss << "AddShape right_leg #000000 line 100 240 140 300" << std::endl;
    oss << "DrawPicture" << std::endl;
    return oss.str();
}

std::string GetPoemParams()
{
    std::ostringstream oss;
    oss << "AddShape text_line1 #000000 text 20 20 24 \"The wind whispers in the treetops,\"" << std::endl;
    oss << "AddShape text_line2 #000000 text 20 50 24 \"The sun shines like a bright sword,\"" << std::endl;
    oss << "AddShape text_line3 #000000 text 20 80 24 \"The river flows, knowing no barriers,\"" << std::endl;
    oss << "AddShape text_line4 #000000 text 20 110 24 \"And in the heart, joy, and in the soul — evening.\""
        << std::endl;

    oss << "AddShape text_line5 #000000 text 20 140 24 \"Flowers bloom in gentle colors,\"" << std::endl;
    oss << "AddShape text_line6 #000000 text 20 170 24 \"Birds sing of the spring day.\"" << std::endl;
    oss << "AddShape text_line7 #000000 text 20 200 24 \"Every moment is a gift, a meeting,\"" << std::endl;
    oss << "AddShape text_line8 #000000 text 20 230 24 \"With the world around, with dreams deep inside.\""
        << std::endl;

    oss << "AddShape text_line9 #000000 text 20 260 24 \"Stars sparkle in the skies above,\"" << std::endl;
    oss << "AddShape text_line10 #000000 text 20 290 24 \"The moon smiles from its height.\"" << std::endl;
    oss << "AddShape text_line11 #000000 text 20 320 24 \"We are all just particles of wonders,\"" << std::endl;
    oss << "AddShape text_line12 #000000 text 20 350 24 \"In this world — of love and dreams.\"" << std::endl;

    oss << "AddShape text_line13 #000000 text 20 380 24 \"So let’s cherish every moment,\"" << std::endl;
    oss << "AddShape text_line14 #000000 text 20 410 24 \"Let’s gather together the flowers of happiness.\""
        << std::endl;
    oss << "AddShape text_line15 #000000 text 20 440 24 \"Inspiration is in every breath,\"" << std::endl;
    oss << "AddShape text_line16 #000000 text 20 470 24 \"In our lives — endless paths.\"" << std::endl;

    oss << "DrawPicture" << std::endl;
    return oss.str();
}

std::string GetLargeStickFigure2Params()
{
    std::ostringstream oss;

    // Original stick figure parts
    oss << "AddShape head #000000 circle 100 50 40" << std::endl; // Head
    oss << "AddShape body #000000 line 100 60 100 240" << std::endl; // Body
    oss << "AddShape left_arm #000000 line 100 70 60 130" << std::endl; // Left Arm
    oss << "AddShape right_arm #000000 line 100 70 140 130" << std::endl; // Right Arm
    oss << "AddShape left_leg #000000 line 100 240 60 300" << std::endl; // Left Leg
    oss << "AddShape right_leg #000000 line 100 240 140 300" << std::endl; // Right Leg

    // Clone and move each part of the stick figure separately
    oss << "CloneShape head head_clone" << std::endl;
    oss << "MoveShape head_clone 50 -20" << std::endl; // Move cloned head

    oss << "CloneShape body body_clone" << std::endl;
    oss << "MoveShape body_clone 50 -20" << std::endl; // Move cloned body

    oss << "CloneShape left_arm left_arm_clone" << std::endl;
    oss << "MoveShape left_arm_clone 50 -20" << std::endl; // Move cloned left arm

    oss << "CloneShape right_arm right_arm_clone" << std::endl;
    oss << "MoveShape right_arm_clone 50 -20" << std::endl; // Move cloned right arm

    oss << "CloneShape left_leg left_leg_clone" << std::endl;
    oss << "MoveShape left_leg_clone 50 -20" << std::endl; // Move cloned left leg

    oss << "CloneShape right_leg right_leg_clone" << std::endl;
    oss << "MoveShape right_leg_clone 50 -20" << std::endl; // Move cloned right leg

    // Draw the original stick figure
    oss << "DrawPicture" << std::endl;

    return oss.str();
}

std::string GetLargeStickFigure3Params()
{
    std::ostringstream oss;

    // Original stick figure parts
    oss << "AddShape head #A00000 circle 100 50 40" << std::endl; // Head
    oss << "AddShape body #0B0000 line 100 60 100 240" << std::endl; // Body
    oss << "AddShape left_arm #00C000 line 100 70 60 130" << std::endl; // Left Arm
    oss << "AddShape right_arm #000D00 line 100 70 140 130" << std::endl; // Right Arm
    oss << "AddShape left_leg #0000E0 line 100 240 60 300" << std::endl; // Left Leg
    oss << "AddShape right_leg #00000F line 100 240 140 300" << std::endl; // Right Leg

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            oss << "DrawPicture" << std::endl;
            oss << "MovePicture 20 0" << std::endl;
        }
        oss << "MovePicture -600 50" << std::endl;
    }


    return oss.str();
}

int main(int argc, char *argv[])
{
    int param = 0;

    // Check if there is one argument provided
    if (argc > 1)
    {
        // Convert the argument to an integer
        param = std::stoi(argv[1]);
    }

    if (param == 0)
    {
        HandleCommands(std::cin, "output.png");
        return 0;
    }

    std::istringstream iss1(GetHomeParams());
    HandleCommands(iss1, "home.png");

    std::istringstream iss2(GetLargeStickFigureParams());
    HandleCommands(iss2, "human.png");

    std::istringstream iss3(GetLargeStickFigure2Params());
    HandleCommands(iss3, "human2.png");

    std::istringstream iss5(GetLargeStickFigure3Params());
    HandleCommands(iss5, "human3.png");

    std::istringstream iss4(GetPoemParams());
    HandleCommands(iss4, "poem.png");

    return 0;
}
