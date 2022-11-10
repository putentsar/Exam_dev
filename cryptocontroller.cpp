#include "cryptocontroller.h"
#include "cryptocontroller.h"
#include <QString>
#include <openssl/evp.h>
#include <QFile>
#include <QIODevice>
#include <QObject>
#include <openssl/conf.h>
#include <QQmlContext>
#include <QDebug>
#include <QClipboard>
#include <QGuiApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QByteArray>
#include <QProcess>
#include <QClipboard>
#include <atlstr.h>
#include <Windows.h>
#include <intrin.h>
#include <iostream>
#include <string.h>
CryptoController::CryptoController(QObject *parent) : QObject(parent)
{

}
void CryptoController::encrypt_login_or_password(QString password) {
    EVP_CIPHER_CTX *ctx;
    if(!(ctx = EVP_CIPHER_CTX_new())){ //EVP_CIPHER_CTX_new() creates a cipher context.
        return;
    }

    //пароль расширяется до ключа из 32 символов
    QString key = password + ((QString)"0").repeated(32 - password.length());

    //инициализирующий вектор для шифра
    iv = (unsigned char*) key.data();

    //инициализация шифра
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cfb(), NULL, (unsigned char*) key.data(), iv))
    {
        return;
    }

    unsigned char ciphertext[256] = {0};//зашифрованные данные
    unsigned char plaintext[256] = {0};//открытый текст
    int len = 0, plaintext_len = 256;//длина блока расшифрования

    //файл, в который записываем вручную текст
    QFile out("C:\\qt projects\\191_331_Revyakin\\out.txt");
    bool is_opened = out.open(QIODevice::ReadOnly);
    if(!is_opened) {
        return;
    }

    //читаем файл порционно, по 256 символов, записываем текст в plaintext,
    //переменная plaintext_len хранит число полученных символов
    plaintext_len = out.read((char *)plaintext, 256);

    //файл, куда записываются зашифрованные данные
    QFile in("C:\\qt projects\\191_331_Revyakin\\in.txt");
    in.open(QIODevice::WriteOnly);

    QByteArray ciphertext_qbyte;//промежуточное звено, которое будет хранить в себе зашифрованные

    //зашифрование текста
    while(plaintext_len > 0){
        if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len)) {
            return;
        }

        ciphertext_qbyte = QByteArray(((char *) ciphertext), len);//преобразование из char в QByteArray
        in.write(ciphertext_qbyte.toBase64());//переводим в формат Base64 и записываем в файл
        plaintext_len = out.read((char *)plaintext, 256);//берем следующие 256 символов
    }

    //закрываем оба файла
    in.close();
    out.close();

    EVP_CIPHER_CTX_free(ctx);

}
bool CryptoController::check_password(QString password) {
//    encrypt_db_file("1327");
    encrypt_login_or_password("1327");
    EVP_CIPHER_CTX *ctx;
    if(!(ctx = EVP_CIPHER_CTX_new())){
        return 0;
    }

    QString key = password + ((QString)"0").repeated(32 - password.length());//пароль расширяется до ключа из 32 символов

    iv = (unsigned char*) key.data();//инициализирующий вектор для шифра

    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cfb(), NULL, (unsigned char*) key.data(), iv)) //инициализация шифра
    {
        return false;
    }

    unsigned char ciphertext[256] = {0};
    unsigned char plaintext[256] = {0};
    int len = 0, plaintext_len = password.length();

    memcpy(plaintext, password.toStdString().c_str(), password.size());


    //введенный ПИН зашифровывается
    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    {
        return false;
    }

    QString password_cipher = (char *)ciphertext;
    QByteArray password_cipher_qbyte = (char*) ciphertext;

    char buffer[256] = {0};
    QFile source_file("C:\\qt projects\\191_331_Revyakin\\password.txt");
    bool is_opened = source_file.open(QIODevice::ReadOnly);
    //source_file.write(password_cipher_qbyte.toBase64());
    source_file.read(buffer, 256);


    source_file.close();
    EVP_CIPHER_CTX_free(ctx);

    //возвращается значение считанного и зашифрованного ПИНа с клавиатуры с уже хранящимся зашифрованным ПИНом в .txt файле
    return QString(buffer) == password_cipher_qbyte.toBase64();
}
