#include "http.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char *http_process(char *request) {
    // 定义和初始化变量
    static char response[4096];
    char method[16], uri[1024], protocol[16];
    char filePath[2048];
    FILE *file;

    // 解析请求
    sscanf(request, "%15s %1023s %15s", method, uri, protocol);

    // 构造文件路径
    sprintf(filePath, "htdocs%s", uri);
    if (strcmp(uri, "/") == 0) {
        // 如果URI是根目录，使用默认页面
        sprintf(filePath, "htdocs/index.html");
    }

    // 检查文件是否存在
    struct stat fileStat;
    if (stat(filePath, &fileStat) < 0) {
        // 文件不存在，返回404
        sprintf(response, "%s 404 Not Found\r\nContent-Type: text/html\r\n\r\n<html><body><h1>404 Not Found</h1></body></html>", protocol);
    } else {
        // 打开文件
        file = fopen(filePath, "r");
        if (file == NULL) {
            // 文件打开失败，返回500
            sprintf(response, "%s 500 Internal Server Error\r\nContent-Type: text/html\r\n\r\n<html><body><h1>500 Internal Server Error</h1></body></html>", protocol);
        } else {
            // 构造成功的响应头
            sprintf(response, "%s 200 OK\r\nContent-Type: text/html\r\n\r\n", protocol);

            // 读取文件内容并追加到响应
            char buffer[1024];
            while (fgets(buffer, sizeof(buffer), file) != NULL) {
                strcat(response, buffer);
            }

            // 关闭文件
            fclose(file);
        }
    }

    return response;
}
