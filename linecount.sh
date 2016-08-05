#########################################################################
# File Name: linecount.sh
# Author: yuhaitao
# mail: acer_yuhaitao@163.com
# Created Time: Mon 20 Jun 2016 08:07:45 AM PDT
#########################################################################
#!/bin/bash
echo "★☆ ★☆ ★☆ ★☆ ★☆★☆★☆ ★☆ ★☆ ★☆ ★☆★"
echo "★☆       统计代码行数        ☆★"
echo "★☆ ★☆ ★☆ ★☆ ★☆★☆★☆ ★☆ ★☆ ★☆ ★☆★"
echo "请输入您要测试的文件目录或文件"
echo $1

echo "正在测试中请稍候....."

echo `date` >> /home/linux/line.txt
echo "总共`sudo find $1 -name "*.c" |xargs cat|grep -v ^$|wc -l`行" >> /home/linux/line.txt
cat /home/linux/line.txt



