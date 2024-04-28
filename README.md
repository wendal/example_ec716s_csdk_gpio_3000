# 演示EC716S控制GPIO,但电平是3.0V

注意: 开机之前不允许任何IO灌入1.8v以上的电压, 否则无法开机

## 编译说明

1. 先确保csdk和luatos均已下载,并顺利编译example项目
2. 修改本代码库project\xmake.lua文件的csdk_root变量, 指向csdk的根目录
3. 在cmd命令下, 先cdd到本代码库的根目录, 然后执行


```
cd project
xmake f --chip_target=ec716s
xmake
```

生成.soc文件, 然后刷机

## 运行效果

[Air780ET开发板演示输出3.0v电压](gpio_3000.mp4)
