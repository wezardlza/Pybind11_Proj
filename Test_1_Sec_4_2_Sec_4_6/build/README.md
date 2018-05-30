# Instructions on CMaking a Solution to this Tiny Project
1. The user's directories should prepared as follows:
  - GitHub
   -- pybind11
     --- CMakeLists.txt //provided by the pybind11 library itself
  - x
   -- Test_2_Sec_5_1_Sec_5_6
    --- CMAkeLists.txt // provided by the user
    --- build
1. Entering the directory '''build''' and type
  '''
  cmake .. -G"Visual Studio 15 Win64"
  '''