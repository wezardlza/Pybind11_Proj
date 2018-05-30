### Instructions on CMaking a Solution to this Tiny Project

1. The user's directories should be prepared as follows (```x``` can be the same directory as ```GitHub```):

    ```
    - GitHub
    
      -- pybind11
    
       --- CMakeLists.txt //provided by the pybind11 library itself
    
    - x
    
      -- Test_3_Sec_5_7_Sec_5_8
    
        --- CMAkeLists.txt // provided by the user
    
        --- build
    ```

1. Enter the directory ```build``` and type

    ```
    cmake .. -G"Visual Studio 15 Win64"
    ```