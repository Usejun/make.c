# 컴파일러와 옵션
CC = gcc
CFLAGS = -Wall -Wextra -Istring -g -w


# 소스 파일
SRC = main.c \
      string/string.c \
	  string/util.c \
      string/view/string_view.c \
      string/view/string_view_mut.c

# 오브젝트 파일 경로를 obj 폴더에 매핑
OBJ = $(patsubst %.c,obj/%.o,$(SRC))

# obj 폴더에 하위 디렉토리 만들기
OBJDIRS = $(sort $(dir $(OBJ)))

# 실행 파일
TARGET = main

# 기본 빌드
all: $(TARGET)

# 링크
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# 오브젝트 파일 컴파일
obj/%.o: %.c
	@mkdir -p $(dir $@)        # obj/ 하위 폴더 생성
	$(CC) $(CFLAGS) -c $< -o $@

# 클린
clean:
	rm -rf obj/ $(TARGET)

.PHONY: all clean
