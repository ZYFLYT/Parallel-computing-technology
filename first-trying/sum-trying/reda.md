# cpp并行计算技术

first test


# 全套 Windows MinGW（CMD终端）OpenMP 命令集
> 环境：你现在这个环境，`sum.cpp` 在 `first-trying` 文件夹，CMD 黑窗口，MinGW g++
> 区分：**编译命令（改代码才执行）**、**运行命令（同一份exe，反复换线程跑）**
> 所有命令直接复制就能跑

## 一、编译类（一共3套，按需选）
> 编译只需要在**修改代码之后执行一次**，生成 `sum.exe`，不改代码不用重复编译
### ① 推荐测速版（日常主力，必用）✅
```cmd
g++ sum.cpp -o sum -fopenmp -O2
```
含义：开启OpenMP + O2优化，适合性能测试，就是你刚才成功跑的这套
### ② 调试版（想看报错、单步调试，不优化）
```cmd
g++ sum.cpp -o sum -fopenmp -O0 -g
```
- `-O0`：关闭优化
- `-g`：加入调试信息，给gdb调试用，**测速不要用这个**
### ③ 激进优化版（O3，浮点顺序会重排，仅计算密集型）
```cmd
g++ sum.cpp -o sum -fopenmp -O3
```
> 注意：求和这种访存程序，O3收益很小，浮点结果可能微小偏差

---
## 二、运行类（5套，编译完sum.exe之后使用，互不干扰）
> 前提：已经编译成功，当前目录有 `sum.exe`
### ① 默认线程运行（自动使用CPU逻辑核数）
```cmd
sum.exe
```
### ② 指定2线程运行
```cmd
set OMP_NUM_THREADS=2
sum.exe
```
### ③ 指定4线程运行（你刚才用的）
```cmd
set OMP_NUM_THREADS=4
sum.exe
```
### ④ 指定8线程运行
```cmd
set OMP_NUM_THREADS=8
sum.exe
```
### ⑤ 清除环境变量，恢复默认线程数
```cmd
set OMP_NUM_THREADS=
sum.exe
```
> ⚠️ CMD特性：`set` 设置的变量**只对当前这一个CMD窗口生效**，关掉窗口就消失，不会改系统全局

---
## 三、PowerShell 版本（如果你以后切到PS终端，和CMD语法不一样！）
### 编译（PS和CMD编译命令完全一样）
```powershell
g++ sum.cpp -o sum -fopenmp -O2
```
### 指定4线程运行（PS单独写法，一行搞定）
```powershell
$env:OMP_NUM_THREADS=4; .\sum.exe
```
### 指定2线程
```powershell
$env:OMP_NUM_THREADS=2; .\sum.exe
```
### 默认线程
```powershell
.\sum.exe
```

---
## 四、Linux / WSL 版本（备用，以后换Linux用）
### 编译
```bash
g++ sum.cpp -o sum -fopenmp -O2
```
### 4线程运行（一行）
```bash
OMP_NUM_THREADS=4 ./sum
```
### 2线程
```bash
OMP_NUM_THREADS=2 ./sum
```

---
## 五、一键脚本（Windows CMD 一键编译+运行，新建 `run.bat`）
新建文本文档，粘贴下面内容，改名为 `run.bat`，放到和sum.cpp同目录
```bat
@echo off
echo ===== 开始编译 =====
g++ sum.cpp -o sum -fopenmp -O2
if %errorlevel% neq 0 (
    echo 编译失败！
    pause
    exit
)
echo 编译成功，4线程运行
set OMP_NUM_THREADS=4
sum.exe
pause
```
以后直接双击 `run.bat`，自动编译+4线程跑。

---
# 极简使用流程（记住这个）
1. 修改代码 → 执行【推荐测速版编译命令】
2. 测试不同线程：复制对应【运行命令】
3. 想换线程：直接重新set + 运行，**不用重新编译**

# 避坑清单
1. 优化是大写 `-O2`，不是数字 `-02`
2. 编译参数 `-fopenmp` 不能丢，丢了没有并行
3. 环境变量 `OMP_NUM_THREADS` 是运行时参数，**写在编译命令里无效**

如果你想要，我可以再给你一套后面学 `schedule`、`reduction` 其他运算符的配套测试命令。