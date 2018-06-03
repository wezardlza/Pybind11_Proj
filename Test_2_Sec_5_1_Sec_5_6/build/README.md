### Instructions on CMaking a Solution to this Tiny Project

1. The user's directories should be prepared as follows (```x``` can be the same directory as ```GitHub```). `index` and `corresponding pybinder11 manual sections` are avitrarily set by the author of this project. 
    They can be changed by a user of the project. 
    ``` 
    - GitHub

        - pybind11

            - CMakeLists.txt // provided by the pybind11 library itself

    - x
        - Test_index_[correspondingPybinder11ManualSections]

            - CMAkeLists.txt // provided by the user

            - build  
    ```

1. Enter the directory ```build``` and type
    ```
    cmake .. -G"Visual Studio 15 Win64"
    ```
