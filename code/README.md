# 代码

各文件夹内容：  
libraries：使用adafruit屏幕绘制所需要的库文件  
CurveGenerator：使用arduino uno输出方波  
TouchPad：使用teensy输出正弦、方波、三角波等波形  

注：由于arduino无法进行真正的模拟输出，而是使用PWM（脉冲宽度调制）。在使用electrovibration技术时PWM的频率还是太低，无法实现真正模拟输出所达到的触觉反馈效果。因而放弃使用arduino，转而使用teensy进行开发。
