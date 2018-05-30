### Instructions on CMaking a Solution to this Tiny Project

1. The user's directories should be prepared as follows (```x``` can be the same directory as ```GitHub```):

    ```
    - GitHub
    
      -- pybind11
    
       --- CMakeLists.txt //provided by the pybind11 library itself
    
    - x
    
      -- Test_1_Sec_4_2_Sec_4_6
    
        --- CMAkeLists.txt // provided by the user
    
        --- build
    ```

1. Entering the directory ```build``` and type

    ```
    cmake .. -G"Visual Studio 15 Win64"
    ```