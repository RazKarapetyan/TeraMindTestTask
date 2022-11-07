# CLI tool under MacOSX
CLI tool to read and write from shared file (Buggy one :D)
### Prepare development environment
1. Install required libs 
   ```bash
   brew install boost 

3. Clone the repository
   ```bash
   # for ssh
   git clone https://github.com/RazKarapetyan/TeraMindTestTask

4. Configure and build the project
   ```bash
   cd Teramind #if not in it already
   mkdir build
   cd build
   cmake .. 
   cmake --build .
   ```
5. Run the app
    ```bash
    ./app/TeraMindTestTask 
    App Usage:
    -h [ --help ]           Display help message
    -p [ --producer ]       Act as a producer
    -c [ --client ]         Act as a client
    -t [ --input-text ] arg Input text
