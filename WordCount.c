#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// 优化分隔符：新增换行、制表符，适配所有文本场景
int isSeparator(char ch) {
    return (ch == ' ' || ch == ',' || ch == '\n' || ch == '\t');
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("用法：%s [-c/-w] 文件名\n", argv[0]);
        printf("示例：%s -c input.txt\n", argv[0]);
        system("pause");
        return 1;
    }

    FILE *fp = fopen(argv[2], "r");
    if (fp == NULL) {
        printf("错误：文件不存在或无法打开！\n");
        system("pause");
        return 1;
    }

    char ch;
    int count = 0;
    if (strcmp(argv[1], "-c") == 0) {
        while ((ch = fgetc(fp)) != EOF) {
            count++;
        }
        printf("字符数：%d\n", count);
    }
    else if (strcmp(argv[1], "-w") == 0) {
        int inWord = 0;
        while ((ch = fgetc(fp)) != EOF) {
            // 非分隔符且未标记单词，计数+标记
            if (!isSeparator(ch) && inWord == 0) {
                inWord = 1;
                count++;
            }
            // 遇到分隔符，重置标记
            else if (isSeparator(ch)) {
                inWord = 0;
            }
        }
        printf("单词数：%d\n", count);
    }
    else {
        printf("错误：参数只能是 -c 或 -w\n");
        fclose(fp);
        system("pause");
        return 1;
    }

    fclose(fp);
    system("pause");
    return 0;
}
