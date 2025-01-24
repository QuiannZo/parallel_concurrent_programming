# ParalellHW



## Name
Zippass_pthread.

## Description for the serial version
The porpuse of the solution is to access protected zip files. To achieve this, i created a solution which uses the libzip library to verify if the password being used is correct or not. The algorithm followed was the following: A function named find_passwords will iterate through all the paths stored in the paths array and apply the find_password function to each. The find_password function will create a loop that goes through all the possible char combinations, no matter the order or size. It has an upper limit set on maxLen. The function will apply the open_file function which will return a 0 if the password given could open and read the contents inside the zip file, and a 1 if it could not. As the loop goes on, if the password is correct, it will add a blank space and the password to the zip file directory stored in paths. At the end the print_data function prints the paths along with their passwords (if found).

## Description of concurrence
The initial recursive algorithm was change to a serial one that uses two for loops to achieve the search of all the necessary passwords. The first for loop iterates through the passwords possible lengths and then goes to the next loop which goes through a range of combinations calculated with the static mapping. Inside the second loop a base change is used and the current password tested.

This version uses threads to acomplish more efficiency and speed. The threads are gathered from the system to see the total number and then each one is created and asigned a range of workload to check. Each of the threads has private data, which they use to get data such as their id. 

## Usage
To use this program, you must run it using a terminal. The format is:

    ./executable -f location/input.txt

With this, you can run the program and wait till it finishes cycling around the possible passwords. This process will take a while.

## Authors and acknowledgment
Main contributor:

    Quiann Zolfaghari. Creator of the proyect.

acknowledgment:

    Chatgpt. The code contains additions of '\0' at the end of the char arrays to avoid segmentation faults. This suggestion was provided by
    the chat bot. Also, general revision of the code was made. webpage: https://chat.openai.com/

    Stackoverflow. The few references found on the internet about libzip were here. I also used a guide to debug from this site.
    webpage: https://stackoverflow.com/

    libzip. The documentation site was used to find the methods to be used and their implementation.
    webpage: https://libzip.org/documentation/zip_fopen.html

    Jeisson ucr. The formula for the ranges was gathered from the material of the curse. website: https://jeisson.ecci.ucr.ac.cr/concurrente/2022b/material/#block_mapping

    