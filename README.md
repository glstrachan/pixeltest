
# Building and Running PixelTest

## Prerequisites

Before building and running PixelTest, ensure you have the following installed on your system:

- **CMake**: Required for configuring and generating the build files. Visit [CMake's official download page](https://cmake.org/download/) for installation instructions.

## Cloning the Repository

First, clone the repository to your local machine using the following command:

```bash
git clone https://github.com/glstrachan/pixeltest.git
cd pixeltest
```

## Building the Project

From the root directory of the project, create a new directory for the build files and navigate into it:

```bash
mkdir build && cd build
```

Configure the project using CMake. This command generates the necessary build files:

```bash
cmake ..
```

Now, compile the project:

```bash
cmake --build .
```

This will create an executable in the `build` directory.

## Running the Executable 🎊

It's crucial to run the executable from the root directory of the project to ensure it can correctly locate the shaders and assets. Navigate back to the root directory:

```bash
cd ..
```

Run the executable from the root directory:

```bash
./build/PixelTest
```

## Troubleshooting

- If you encounter issues related to missing shaders or assets, confirm that you're running the executable from the project's root directory.
- Ensure all dependencies, including CMake, are correctly installed and up-to-date.

For more help or information, please refer to the project's README or contact the project maintainers.
