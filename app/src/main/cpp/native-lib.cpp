#include <jni.h>
#include <string>
//定义与JAVA文件test类相同的结构，用于数据实体转换
struct myStruct{
    int id;
    uint8_t lab;
    long id_card;
    std::string name;
}new_struct;

//导出C函数形式的方法通过JNI提供给JAVA调用
//返回jstring类型相当于JAVA中的String类对象
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_mylib_MainActivity_stringFromJNI(
        JNIEnv* env,//JNI环境
        jobject) //主Activity对象
{
    std::string hello = "Hello from C++";//实例化C++标准字符串
    return env->NewStringUTF(hello.c_str());//转换为jstring并返回
}

//导出C函数形式的方法通过JNI提供给JAVA调用
extern "C" JNIEXPORT jobject JNICALL
Java_com_example_mylib_MainActivity_objFromJNI(JNIEnv *env, //JNI环境
                                               jobject thiz, //主Activity对象
                                               jobject obj) //test类对象参数
{
    //C++实例化结构体
    new_struct.id=0001;
    new_struct.lab=0xff;
    new_struct.id_card=0xffff+128;
    new_struct.name="jni_test_object_return";

    //C++ JNI 操作JAVA类型
    jclass c = env->FindClass("com/example/mylib/test"); //通过包名取test类对象
    //GetFieldID(类对象，字段名，字段名签名)
    jfieldID f1=env->GetFieldID(c,"id","I"); //取字段id标识
    jfieldID f2=env->GetFieldID(c,"lab", "C");//取字段lab标识
    jfieldID f3=env->GetFieldID(c,"id_card","J");//取字段id_card标识
    jfieldID f4=env->GetFieldID(c,"name", "Ljava/lang/String;");//取字段name标识
    //获取字段值
    jint id=env->GetIntField(obj,f1);
    jchar lab=env->GetCharField(obj,f2);
    jlong id_card=env->GetLongField(obj,f3);
    jstring name=(jstring)env->GetObjectField(obj,f4);
    //设置字段值
    env->SetIntField(obj,f1,new_struct.id+10);
    env->SetCharField(obj,f2,new_struct.lab+10);
    env->SetLongField(obj,f3,(long)new_struct.id_card+10);
    env->SetObjectField(obj,f4, env->NewStringUTF(new_struct.name.c_str())); //设置JNI对象
    return obj;//返回JNI对象，相当于test类对象
}