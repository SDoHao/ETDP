# ETDP
Electrochemical Test Data Processing

处理Path路径下的保存格式为scv的所有电化学数据文件

修改规则文件Rule.ini
Path=. 默认当前文件夹，也可以是E:\\Code\\1\\,注意是双斜杠
Radius半径，单位mm
RefeElecRode 参比电极 SCE 甘汞电极 AgCl 氯化银电极
Mode CV数据  LSV数据
Start=18000 从18000行开始输出数据
End=20000 输出到2000行的数据为止
Test ORR 待转换的ORR数据
Convert 转换为RHE，标准氢电极

运行时不要打开Output.csv
