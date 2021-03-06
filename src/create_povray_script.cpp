#include <stdio.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

#include "convert_poses.hpp"

void usage(const char* progname)
{
    fprintf( stderr, "Usage: %s -f FILENAME [options]\n"
            "\n"
            "Options:\n"
            "   -f (filename)   Set file path to poses txt file (REQUIRED)\n"
            "   -h              This help message\n"
            , progname);
    exit(1);
}

int main (int argc, char** argv)
{
    int c;
    std::string pose_filepath;

    while ((c = getopt(argc, argv, "f:h")) >= 0)
    {
        switch (c) {
            case 'f':
                pose_filepath.insert(0, optarg);
                std::cout<<"Using file "<<pose_filepath<<std::endl;
                break;
            case 'h':
            default:
                usage(argv[0]);
                break;
        }
    }
    if (pose_filepath.size() == 0)
    {
        usage(argv[0]);
    }
    
    std::string filename;
    std::size_t find_dot = pose_filepath.find(".txt");
    std::size_t find_slash = pose_filepath.find_last_of('/');
    filename = pose_filepath.substr(find_slash+1,find_dot-find_slash-1);

    ConvertPoses poses(pose_filepath, (filename + ".sh").c_str());
    std::vector<float> pose;

    for (pose = poses.readPoseFromFile(); pose.size() != 0;
         pose = poses.readPoseFromFile())
    {
        poses.writePose(pose);
    }
    poses.closeFile();

    return 0;    
}
