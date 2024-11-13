import os

path = input("请输入视频目录路径：")
dir_name = os.path.basename(path)
if "\\" in path:
    path = path.replace("\\", "/")

for root, dirs, files in os.walk(path):
    for file in files:
        if file == "video.mp4":
            file_path = os.path.join(root, file)
            dir_path = os.path.dirname(file_path)
            parent_path = os.path.dirname(dir_path)
            new_file_name = os.path.basename(dir_path) + ".mp4"
            new_file_path = os.path.join(parent_path, new_file_name)
            os.rename(file_path, new_file_path)

for file in os.listdir(path):
    if file != dir_name:
        old_path = os.path.join(path, file)
        new_path = os.path.join(parent_path, file)
        os.rename(old_path, new_path)

print("操作成功！")