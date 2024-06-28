package com.example.mylib;
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;
import com.example.mylib.databinding.ActivityMainBinding;
public class MainActivity extends AppCompatActivity {
    //加载原生静态库
    static {
        System.loadLibrary("mylib");//JNI生成的静态库名
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        TextView tv = binding.sampleText;
        tv.setText(stringFromJNI());

        //创建test类对象
        test obj=new test();
        //类成员赋值
        obj.id=0x0001;
        obj.lab= 0xff;
        obj.id_card=0xffff+128;
        obj.name="java_class_value_to_cpp";
        //传递给JNI原生C++函数
        obj = objFromJNI(obj);
        System.out.println(obj.name);//输出函数处理后的并返回的值
    }
    //C++原生库实现
    public native String stringFromJNI();  //String相当于JNI中jstring

    public native test objFromJNI(test obj);
}