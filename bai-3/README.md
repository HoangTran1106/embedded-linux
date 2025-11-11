# Linux System Programming Exercises
## Bài tập Lập trình Hệ thống Linux

---

## Exercise 1: File Metadata Checker (filestat)
### Bài tập 1: Trình kiểm tra Siêu dữ liệu File

**Description / Mô tả:**
A command-line tool that displays file metadata using the `lstat()` system call.
Công cụ dòng lệnh hiển thị siêu dữ liệu của file sử dụng lệnh gọi hệ thống `lstat()`.

**Features / Tính năng:**
- Displays file type (Regular File, Directory, Symbolic Link)
- Shows file size in bytes
- Displays last modification time
- Uses `lstat()`, `S_ISREG()`, `S_ISDIR()`, `S_ISLNK()` macros

**Compilation / Biên dịch:**
```bash
gcc -Wall -o filestat filestat.c
# OR / HOẶC
make filestat
```

**Usage / Sử dụng:**
```bash
./filestat <file_path>

# Examples / Ví dụ:
./filestat filestat.c          # Check regular file
./filestat .                   # Check directory
./filestat /usr/bin/python3    # Check symbolic link (if exists)
```

**Expected Output / Kết quả mong đợi:**
```
=== FILE INFORMATION ===
File Path: filestat.c
File Type: Regular File
Size: 1234 bytes
Last Modified: 2025-11-11 10:30:45
========================
```

---

## Exercise 2: Process Operations
### Bài tập 2: Thao tác với Tiến trình

### Task 1: Basic Process Creation and Cleanup
### Bài tập 1: Khởi tạo và Thu dọn Tiến trình

**File:** `process_basic.c`

**Description / Mô tả:**
Demonstrates basic process lifecycle: creation with `fork()`, execution, termination, and parent waiting with `wait()`.
Minh họa vòng đời cơ bản của tiến trình: tạo với `fork()`, thực thi, kết thúc, và cha chờ đợi với `wait()`.

**Key Concepts / Khái niệm chính:**
- `fork()` - creates child process
- `wait()` - parent waits for child
- `WIFEXITED()` - checks if child exited normally
- `WEXITSTATUS()` - gets child's exit code
- Parent and child PIDs

**Compilation / Biên dịch:**
```bash
gcc -Wall -o process_basic process_basic.c
# OR / HOẶC
make process_basic
```

**Usage / Sử dụng:**
```bash
./process_basic
```

---

### Task 2: Exec and Environment Variables
### Bài tập 2: Thay thế Mã thực thi và Tương tác với Môi trường

**File:** `process_exec.c`

**Description / Mô tả:**
Demonstrates how a process can replace its code using `exec()` family and interact with environment variables.
Minh họa cách tiến trình thay thế mã lệnh bằng họ hàm `exec()` và tương tác với biến môi trường.

**Key Concepts / Khái niệm chính:**
- `setenv()` - sets environment variable
- `getenv()` - reads environment variable
- `execlp()` - replaces process image
- Address space replacement after `exec()`

**Compilation / Biên dịch:**
```bash
gcc -Wall -o process_exec process_exec.c
# OR / HOẶC
make process_exec
```

**Usage / Sử dụng:**
```bash
./process_exec
```

**What happens after exec()? / Điều gì xảy ra sau exec()?**
- Entire address space is replaced / Toàn bộ không gian địa chỉ bị thay thế
- Old program code is discarded / Mã lệnh cũ bị loại bỏ
- New program (ls) is loaded / Chương trình mới (ls) được nạp
- Same PID, but completely new process image / Cùng PID nhưng hoàn toàn là tiến trình mới
- Code after exec() never executes / Mã lệnh sau exec() không bao giờ thực thi

---

### Task 3a: Zombie Process
### Bài tập 3a: Tiến trình Zombie

**File:** `process_zombie.c`

**Description / Mô tả:**
Demonstrates a zombie process - a terminated child that hasn't been reaped by parent.
Minh họa tiến trình zombie - tiến trình con đã kết thúc nhưng chưa được cha thu dọn.

**Key Concepts / Khái niệm chính:**
- Child exits immediately / Con thoát ngay lập tức
- Parent doesn't call `wait()` / Cha không gọi `wait()`
- Process becomes `<defunct>` / Tiến trình trở thành `<defunct>`
- Zombie holds process table entry / Zombie giữ mục trong bảng tiến trình

**Compilation / Biên dịch:**
```bash
gcc -Wall -o process_zombie process_zombie.c
# OR / HOẶC
make process_zombie
```

**Usage / Sử dụng:**
```bash
./process_zombie
```

**To observe zombie / Để quan sát zombie:**
While program is running, open another terminal:
Trong khi chương trình chạy, mở terminal khác:
```bash
ps aux | grep defunct
# OR / HOẶC
ps -l | grep Z
```

**Why zombies exist? / Tại sao zombie tồn tại?**
- Allows parent to retrieve child's exit status / Cho phép cha lấy mã thoát của con
- Holds minimal resources (just process table entry) / Giữ tài nguyên tối thiểu
- Cleaned up when parent calls `wait()` or parent dies / Được dọn khi cha gọi `wait()` hoặc cha chết

---

### Task 3b: Orphan Process
### Bài tập 3b: Tiến trình Orphan (Mồ côi)

**File:** `process_orphan.c`

**Description / Mô tả:**
Demonstrates an orphan process - a running process whose parent has terminated.
Minh họa tiến trình orphan - tiến trình đang chạy mà cha đã kết thúc.

**Key Concepts / Khái niệm chính:**
- Parent exits before child / Cha thoát trước con
- Child continues running / Con tiếp tục chạy
- `init`/`systemd` (PID 1) adopts orphan / `init`/`systemd` nhận con nuôi
- PPID changes to 1 / PPID đổi thành 1

**Compilation / Biên dịch:**
```bash
gcc -Wall -o process_orphan process_orphan.c
# OR / HOẶC
make process_orphan
```

**Usage / Sử dụng:**
```bash
./process_orphan
```

**What to observe? / Quan sát gì?**
Watch the PPID change from original parent to 1 (init/systemd)
Quan sát PPID đổi từ cha ban đầu sang 1 (init/systemd)

**Why orphans exist? / Tại sao orphan tồn tại?**
- Prevents invalid parent PIDs / Ngăn PID cha không hợp lệ
- Maintains process hierarchy / Duy trì cây tiến trình
- Orphans run normally under new parent / Orphan chạy bình thường dưới cha mới
- Not a problem - intentional system behavior / Không phải vấn đề - hành vi hệ thống có chủ đích

---

## Quick Start / Bắt đầu nhanh

**Compile all / Biên dịch tất cả:**
```bash
make all
```

**Clean up / Dọn dẹp:**
```bash
make clean
```

**Test filestat / Kiểm tra filestat:**
```bash
make test_filestat
```

**Test process programs / Kiểm tra chương trình tiến trình:**
```bash
make test_process
```

---

## Key System Calls / Lệnh gọi hệ thống chính

### File Operations:
- `lstat()` - Get file metadata without following symlinks
- `ctime()` / `strftime()` - Convert timestamp to human-readable format

### Process Operations:
- `fork()` - Create new process
- `wait()` / `waitpid()` - Wait for child process
- `exec()` family - Replace process image
- `exit()` - Terminate process
- `getpid()` - Get process ID
- `getppid()` - Get parent process ID
- `setenv()` / `getenv()` - Environment variable operations

---

## Important Notes / Lưu ý quan trọng

1. **Zombie Process:**
   - Temporary state when child exits before parent calls wait()
   - Holds minimal resources
   - Not harmful in small numbers
   - Cleaned up automatically

2. **Orphan Process:**
   - Child continues running after parent dies
   - Adopted by init/systemd
   - Completely normal and intentional
   - Not a problem

3. **exec() Behavior:**
   - Replaces entire process image
   - Same PID, new program
   - Code after exec() never runs
   - File descriptors can be inherited

---

## Author / Tác giả
DevLinux Academy
Embedded Systems Training

## Contact / Liên hệ
Email: devlinux.edu@gmail.com
Phone: 0877123348
