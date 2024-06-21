#include <stdio.h>
// Declares printf(), fprintf(), fopen(), fclose().
#include <stdlib.h>
// Declares exit().
#include <fcntl.h>
// O_RDONLY, O_WRONLY
#include <unistd.h>
// Declares read(), write(), close(), fork(), exec()
#define BUF_SIZE 200

// Function declarations
int compare(char* file1, char* file2);
int differentCreate(char* file1, char* file2);
void Error(char* msg);

//argc : number recived argument (2)
//argv[0] : name of program
//argv[1] : file 1
//argv[2] : file 2

int main(int argc, char* argv[])
{
    if (argc != 3)
        Error("Invalid aguments number");

    char* file1 = argv[1];
    char* file2 = argv[2];

    // Call compare function
    compare(file1, file2);
    return 0;
}


// function get 2 files, check if the files indenticals
int compare(char* file1, char* file2)
{

    int fd_file1, fd_file2, bytes_file1, bytes_file2;
    char buff1[BUF_SIZE];     //buffer file 1
    char buff2[BUF_SIZE];     //buffer file 2

    //open file1
    if ((fd_file1 = open(file1, O_RDONLY)) == -1)
    {
        perror("open file1");
        return (-1);
    }
    //open file2
    if ((fd_file2 = open(file2, O_RDONLY)) == -1)
    {
        perror("open file2");
        close(fd_file1);
        return (-1);
    }

    // Read initial buffers
    if (((bytes_file1 = read(fd_file1, buff1, BUF_SIZE)) == -1) || ((bytes_file2 = read(fd_file2, buff2, BUF_SIZE)) == -1))
    {
        close(fd_file1);
        close(fd_file2);
        return -1;
    }

    // keep reading all the files, if diffrent stop and oparate function 
    while (bytes_file1 > 0 && bytes_file2 > 0)
    {
        //if read diffrent number of bytes   - diffrent
        if (bytes_file1 != bytes_file2)
        {
            printf("Different files\n");
            differentCreate(file1, file2);
            return 0;     // files different
        }
        // if content of buffer1 != buffer2 - diffrent
        for (int i = 0; i < bytes_file1; i++)
        {
            if (buff1[i] != buff2[i])
            {
                printf("Different files\n");
                differentCreate(file1, file2);
                return 0;  // files different
            }
        }
        //read the next buffer1 and buffer 2
        bytes_file1 = read(fd_file1, buff1, BUF_SIZE);
        bytes_file2 = read(fd_file2, buff2, BUF_SIZE);
    }


    // Check if both files reached EOF
    if (bytes_file1 == 0 && bytes_file2 == 0)
    {
        printf("Identical files\n");
    }
    else
    {
        //from here the case is: one file is longer than the other
        printf("Different files\n");
        differentCreate(file1, file2);
    }

    // Close files
    close(fd_file1);
    close(fd_file2);

    return 0;  // Files are different
}




// functino get 2 diffrent files, create 'compare.txt'
// write "Different file" and then  file1 and file2 
int differentCreate(char* file1, char* file2)
{

    int fd_file1, fd_file2, fd_write, bytes_read, bytes_write;
    char buff[BUF_SIZE];


    //open file1
    if ((fd_file1 = open(file1, O_RDONLY)) == -1)
    {
        perror("open file1");
        return -1;
    }
    //open file2
    if ((fd_file2 = open(file2, O_RDONLY)) == -1)
    {
        perror("open file2");
        close(fd_file1);
        return -1;
    }
    //create 'compare.txt' file and open
    if ((fd_write = open("compare.txt", O_WRONLY | O_CREAT, 0664)) == -1)
    {
        perror("open compare.txt");
        close(fd_file1);
        close(fd_file2);
        return -1;
    }

    //read file 1 and write to 'compare.txt'
    while ((bytes_read = read(fd_file1, buff, BUF_SIZE)) > 0)
    {
        bytes_write = write(fd_write, buff, bytes_read);  //write
        if (bytes_write == -1)
        {
            perror("write compare.txt");
            close(fd_file1);
            close(fd_file2);
            close(fd_write);
            return -1;
        }
    }
    if (bytes_read == -1)
    {
        perror("read file1");
        close(fd_file1);
        close(fd_file2);
        close(fd_write);
        return -1;
    }

    //read file 2 and write to 'compare.txt'
    while ((bytes_read = read(fd_file2, buff, BUF_SIZE)) > 0)
    {
        bytes_write = write(fd_write, buff, bytes_read);
        if (bytes_write == -1)
        {
            perror("write compare.txt");
            close(fd_file1);
            close(fd_file2);
            close(fd_write);
            return -1;
        }
    }
    if (bytes_read == -1)
    {
        perror("read file2");
        close(fd_file1);
        close(fd_file2);
        close(fd_write);
        return -1;
    }

    //finish closing files
    close(fd_file1);
    close(fd_file2);
    close(fd_write);

    return 0;
}

void Error(char* msg)
{
    fprintf(stderr, "Error: %s\n", msg); //stderr Error output
    exit(1); // Exit with error status
}

