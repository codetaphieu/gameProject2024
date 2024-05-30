# Toptep Bird

## Giới Thiệu
Toptep Bird là một trò chơi đơn giản nhưng thú vị, thách thức khả năng điều khiển và phản xạ của người chơi. Trò chơi được lập trình bằng ngôn ngữ C++ và sử dụng thư viện đồ họa SDL2.
## Chức năng chính
- **Play**: Bắt đầu trò chơi.
- **Options**: Điều chỉnh cài đặt độ khó.
- **Quit**: Thoát khỏi trò chơi.
- **GameOver**: Nút replay hoặc thoát.
- **Scores**: Tính điểm qua mỗi màn chơi.
- **Music**: Hiệu ứng âm thanh qua mỗi lần thao tác.
## Cách Chơi
- Nhấn phím bất kỳ để làm cho chú chim bay lên.
- Tránh va chạm vào các cột ống và không để chú chim rơi xuống đất.
- Cố gắng bay qua càng nhiều cột ống càng tốt để đạt điểm cao.

## Cài Đặt
### Yêu Cầu Hệ Thống
- C++ Compiler (GCC, Clang, v.v.)
- Thư viện SDL2, SDL2_image, SDL2_ttf, SDL2_mixer
- Hệ điều hành hỗ trợ (Windows, macOS)

### Hướng Dẫn Cài Đặt
1. Cài đặt SDL2:
    - Trên macOS:
      ```bash
      brew install sdl2 sdl2_image sdl2_mixer sdl2_ttf
    - Trên Windows:
      ```bash
      Tải xuống SDL2, SDL2_image, SDL2_mixer, SDL2_ttf từ trang chủ [SDL2](https://www.libsdl.org/download-2.0.php) và làm theo hướng dẫn cài đặt.
      ```

2. Clone repo này về máy của bạn:
    ```bash
    git clone https://github.com/codetaphieu/gameProject2024.git
    ```
3. Di chuyển vào thư mục dự án:
    ```bash
    cd gameProject2024
    ```
4. Biên dịch mã nguồn:
    ```bash
    g++ -o gameProject2024 main.cpp bird.cpp pipe.cpp game_object.cpp total.cpp -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
    ```

## Sử Dụng
Chạy trò chơi bằng lệnh sau:
```bash
./gameProject2024
```

## Tài Liệu Tham Khảo
- lazyfoo.net
- codelearn.io
