# 选择一些有代表性的同音字（为了演示，不遍历全部）
he_chars = ['合', '何', '和', '核', '阖']  # 部分 hé 音字
yi_chars = ['一', '意', '异', '益', '逸']  # 部分 yì 音字
wei_chars = ['为', '位', '未', '味', '尉']  # 部分 wèi 音字

print("一些‘hé yì wèi’的趣味组合：")
for he in he_chars:
    for yi in yi_chars:
        for wei in wei_chars:
            print(f"{he}{yi}{wei}", end=", ")