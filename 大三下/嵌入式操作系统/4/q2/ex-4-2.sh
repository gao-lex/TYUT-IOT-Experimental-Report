#!/bin/bash
read -p "请输入您的命令  " command
if [ "$command" = "exit" ]
then
    exit 1
else
    echo `$command`
fi