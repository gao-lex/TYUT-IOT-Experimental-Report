```bash
#!/bin/bash
ls -al
find . -name "*.sh" 
# ex-4.sh > ex-4-ans.txt
```

```bash
#!/bin/bash
read -p "请输入您的命令  " command
if [ "$command" = "exit" ]
then
    exit 1
else
    echo `$command`
fi
```
