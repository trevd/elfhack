LOCAL_PATH:= $(call my-dir)

ELFUTILS_PATH := $(LOCAL_PATH)/../../elfutils

libelf_examples_common_cflags := \
	-Wno-unused-parameter \

libelf_examples_common_includes := \
	$(ELFUTILS_PATH)/libelf \
	$(ELFUTILS_PATH)/0.153/libelf


#========= get-elf-type ============

include $(CLEAR_VARS)
LOCAL_CLANG := true
LOCAL_CFLAGS := $(libelf_examples_common_cflags)
LOCAL_SRC_FILES := get-elf-type.c
LOCAL_C_INCLUDES := $(libelf_examples_common_includes) 
LOCAL_STATIC_LIBRARIES := libelf
LOCAL_MODULE := get-elf-type
include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)
LOCAL_CFLAGS := -D_GNU_SOURCE $(libelf_examples_common_cflags)
LOCAL_SRC_FILES := get-elf-type.c
LOCAL_C_INCLUDES := $(libelf_examples_common_includes) 
LOCAL_STATIC_LIBRARIES := libelf
LOCAL_MODULE := get-elf-type
include $(BUILD_HOST_EXECUTABLE)

#========= print-elf-header ============

include $(CLEAR_VARS)
LOCAL_CLANG := true
LOCAL_CFLAGS := $(libelf_examples_common_cflags)
LOCAL_SRC_FILES := print-elf-header.c
LOCAL_C_INCLUDES := $(libelf_examples_common_includes) 
LOCAL_STATIC_LIBRARIES := libelf
LOCAL_MODULE := print-elf-header
include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)
LOCAL_CFLAGS := -D_GNU_SOURCE $(libelf_examples_common_cflags)
LOCAL_SRC_FILES := print-elf-header.c
LOCAL_C_INCLUDES := $(libelf_examples_common_includes) 
LOCAL_STATIC_LIBRARIES := libelf
LOCAL_MODULE := print-elf-header
include $(BUILD_HOST_EXECUTABLE)
