1. vscode只是一款文本编辑器，所有的功能都通过插件提供，安装完插件后，重启vscode以生效插件；

2. 在vscode中对工程进行配置之后，会在工程文件夹中产生.vscode文件夹，里面是.json文件，json文件中的配置对文件夹中的代码文件产生作用；

3. 配置C++开发换环境
   - 配置编译器
     - control + shift + P 调出命令面板,输入C/C++，选择“编辑配置json”,进入配置，会生成.vscode和配置json文件。
     - compilerPath  ： 编译器路径
   - 配置构建任务，告诉vscode如何编译程序
     - control + shift + P调出命令面板，输入tasks,选择“Tasks:Configure Default Build Task”
   - 配置调试
   
   vscode 配置 cmake、cpp开发环境 参考：https://computingonplains.wordpress.com/building-c-applications-with-cmake-and-visual-studio-code/
   
4. 