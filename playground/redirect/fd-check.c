#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

// int main() {
//     int fd;
//     fd = fileno(stdin);
//     printf("File descriptor for stdin: %d\n", fd);

//     // 入力ファイルディスクリプターを変更する例
//     int new_fd = open("new_input_file.txt", O_RDONLY);
//     dup2(new_fd, STDIN_FILENO);

//     // 新しい入力ファイルディスクリプターを取得する
//     int current_fd;
//     current_fd = fileno(stdin);
//     printf("Current file descriptor for stdin: %d\n", current_fd);

//     return 0;
// }

int main() {
    int fd;
    fd = fileno(stdin);
    printf("File descriptor for stdin: %d\n", fd);

    // 入力ファイルディスクリプターを変更する例
    int new_fd = open("new_input_file.txt", O_RDONLY);
    dup2(new_fd, STDIN_FILENO);

    // 新しい入力ファイルディスクリプターのフラグを取得する
    int flags;
    flags = fcntl(STDIN_FILENO, F_GETFL);
    printf("Flags for stdin: %d\n", flags);

    return 0;
}
