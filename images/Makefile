# Makefile for converting WebP to PNG

# 设置变量
SRC_DIR := .
DEST_DIR := .

# 获取所有WebP文件
WEBP_FILES := $(wildcard $(SRC_DIR)/*.webp)

# 将WebP文件转换为PNG文件
PNG_FILES := $(patsubst $(SRC_DIR)/%.webp,$(DEST_DIR)/%.png,$(WEBP_FILES))

# 默认目标，将所有WebP文件转换为PNG
all: $(PNG_FILES)

# 将WebP文件转换为PNG
$(DEST_DIR)/%.png: $(SRC_DIR)/%.webp
	convert $< $@

# 清理生成的PNG文件
clean:
	rm -f $(DEST_DIR)/*.png

# 定义伪目标，防止与实际文件冲突
.PHONY: all clean

