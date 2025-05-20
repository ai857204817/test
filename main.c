#include <stdio.h>
#include <string.h>

// 异或加密函数
void xor_encrypt(char *data, char *key, char *output) {
    int data_len = strlen(data);
    int key_len = strlen(key);
    
    for (int i = 0; i < data_len; i++) {
        // 使用异或运算对字符进行加密
        output[i] = data[i] ^ key[i % key_len];
    }
    output[data_len] = '\0'; // 添加结束符
}

// 异或解密函数
void xor_decrypt(char *encrypted_data, char *key, char *output) {
    // 实际上，异或加密和解密使用相同的函数和密钥
    xor_encrypt(encrypted_data, key, output);
}

int main() {
    char original_data[] = "这是一个示例文本";
    char encryption_key[] = "密钥";
    char encrypted_data[100];
    char decrypted_data[100];

    // 加密数据
    xor_encrypt(original_data, encryption_key, encrypted_data);
    printf("加密后的数据: %s\n", encrypted_data);

    // 解密数据
    xor_decrypt(encrypted_data, encryption_key, decrypted_data);
    printf("解密后的数据: %s\n", decrypted_data);

    // 确认解密后的数据与原始数据相同
    if (strcmp(original_data, decrypted_data) != 0) {
        printf("解密后的数据与原始数据不匹配\n");
    } else {
        printf("解密成功，数据与原始数据匹配\n");
    }

    return 0;
}
