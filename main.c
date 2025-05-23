#include <stdint.h>
#include <stdio.h>

/**
 * 计算MODBUS CRC-16校验值。
 *
 * @param crc 上一次的CRC校验结果，第一次调用时应传入0xFFFF。
 * @param data 待计算的数据指针。
 * @param length 待计算的数据长度。
 * @return 计算得到的新的CRC校验结果。
 */
uint16_t calc_crc16(uint16_t crc, const uint8_t *data, size_t length) {
    uint16_t polynomial = 0xA001; // MODBUS CRC-16多项式
    size_t index = 0;

    // 对每个字节进行处理
    while (index < length) {
        crc ^= data[index++] << 8; // 将当前字节与crc的高8位进行异或操作

        // 对当前字节进行8位处理
        for (uint8_t bit = 0; bit < 8; bit++) {
            if (crc & 0x8000) { // 检查最高位是否为1
                crc = (crc << 1) ^ polynomial; // 左移一位后与多项式异或
            } else {
                crc <<= 1; // 左移一位
            }
        }
    }

    // MODBUS CRC-16需要进行字节交换
    return (crc >> 8) | (crc << 8);
}

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


    uint8_t data[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x0A}; // 示例数据
    size_t length = sizeof(data) / sizeof(data[0]);
    uint16_t crc = 0xFFFF; // 初始CRC值

    crc = calc_crc16(crc, data, length);

    printf("one git\r\n");
    printf("hello world 222\r\n");
    printf("one\r\n");
    printf("two\r\n");
    printf("MODBUS CRC-16: 0x%04X\r\n", crc); // 打印CRC校验结果

	printf("hello world 333 添加代码\r\n");
		
    return 0;
}
