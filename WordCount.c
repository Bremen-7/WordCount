#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// 判断是否为单词分隔符（空格、逗号）
int isSeparator(char ch) {
    return (ch == ' ' || ch == ',');
}

int main(int argc, char *argv[]) {
    // 参数校验：必须传入2个参数（控制参数+文件名）
    if (argc != 3) {
        printf("用法：%s [-c/-w] 文件名\n", argv[0]);
        printf("示例：%s -c input.txt\n", argv[0]);
        system("pause"); // 防闪退，查看提示信息
        return 1;
    }

    // 以只读方式打开目标文本文件
    FILE *fp = fopen(argv[2], "r");
    if (fp == NULL) {
        printf("错误：文件不存在或无法打开！\n");
        printf("请确认input.txt与exe文件放在同一文件夹\n");
        system("pause"); // 防闪退，查看报错信息
        return 1;
    }

    char ch;
    int count = 0;
    // 字符统计逻辑 -c
    if (strcmp(argv[1], "-c") == 0) {
        while ((ch = fgetc(fp)) != EOF) {
            count++; // 所有字符均计数，包含空格、Tab、换行
        }
        printf("字符数：%d\n", count);
    }
    // 单词统计逻辑 -w
    else if (strcmp(argv[1], "-w") == 0) {
        int inWord = 0; // 标记是否处于单词中，0=不在，1=在
        while ((ch = fgetc(fp)) != EOF) {
            if (!isSeparator(ch) && inWord == 0) {
                inWord = 1;
                count++;
            } else if (isSeparator(ch)) {
                inWord = 0;
            }
        }
        printf("单词数：%d\n", count);
    }
    // 非法参数提示
    else {
        printf("错误：参数只能是 -c 或 -w\n");
        fclose(fp);
        system("pause");
        return 1;
    }

    fclose(fp);
    system("pause"); // 防止运行完毕直接闪退，查看统计结果
    return 0;
}
