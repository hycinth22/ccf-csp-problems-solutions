//
// Created by inked on 2019/12/10 0010.
//

#include <bits/stdc++.h>

using namespace std;

struct pixel {
    int r, g, b;

    bool operator==(const pixel &rhs) const {
        return r == rhs.r && g == rhs.g && b == rhs.b;
    }

    bool operator!=(const pixel &rhs) const {
        return !operator==(rhs);
    }
};

int main() {
    // freopen("sample8.in", "r", stdin);
    ios_base::sync_with_stdio(0);
    int m, n; // m宽 n高
    cin >> m >> n;
    int blockWidth, blockHeight; // 每一小块的宽高，不要误认为是块个数
    cin >> blockWidth >> blockHeight;
    vector <vector<pixel>> img(m, vector<pixel>(n));
    // 这里m和n容易搞反
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            cin.ignore(numeric_limits<streamsize>::max(), '#');
            static string colorstr;
            getline(cin, colorstr);
            if (colorstr.back() == '\r') {
                colorstr.pop_back(); // getline不会将分隔符（换行）纳入。但如果输入文件是CRLF（\r\n），而程序在unix编译，则可能除去\n而保留\r
            }
            pixel &p = img[i][j];
            if (colorstr.size() == 6) {
                // #123456 (0x12, 0x34, 0x56)
                p.r = stoi(colorstr.substr(0, 2), 0, 16);
                p.g = stoi(colorstr.substr(2, 2), 0, 16);
                p.b = stoi(colorstr.substr(4, 2), 0, 16);
            } else if (colorstr.size() == 3) {
                // #123 = #112233
                p.r = stoi(colorstr.substr(0, 1), 0, 16);
                p.r += p.r * 16;
                p.g = stoi(colorstr.substr(1, 1), 0, 16);
                p.g += p.g * 16;
                p.b = stoi(colorstr.substr(2, 1), 0, 16);
                p.b += p.b * 16;
            } else if (colorstr.size() == 1) {
                // #1 = #111111
                int c = stoi(colorstr.substr(0, 1), 0, 16);
                p.r = p.g = p.b = c * 17;
            } else {
                exit(111);
            }
        }
    }
    // calc average value for each block
    int cntX = m / blockWidth, cntY = n / blockHeight; // X/Y方向上的块个数
    vector <vector<pixel>> blocks(cntX, vector<pixel>(cntY));
    // 这里x和y也也容易搞反
    for (int j = 0; j < cntY; j++) {
        for (int i = 0; i < cntX; i++) {
            // calc this block
            static pixel sum;
            sum ={.r=0, .g=0, .b=0};
            size_t cnt = 0;
            for (int y = j * blockHeight; y < (j + 1) * blockHeight; y++) {
                for (int x = i * blockWidth; x < (i + 1) * blockWidth; x++) {
                    sum.r += img[x][y].r;
                    sum.g += img[x][y].g;
                    sum.b += img[x][y].b;
                    cnt++;
                }
            }
            blocks[i][j].r = sum.r / cnt;
            blocks[i][j].g = sum.g / cnt;
            blocks[i][j].b = sum.b / cnt;
        }
    }
    // output sequence
    pixel defcolor{.r=0, .g=0, .b=0}; // black
    pixel cur = defcolor;
    stringstream ss;
    for (int j = 0; j < cntY; j++) {
        for (int i = 0; i < cntX; i++) {
            if (blocks[i][j] != cur) {
                // need to modify the background color
                if (blocks[i][j] == defcolor) {
                    ss << "\033[0m";
                } else {
                    ss << "\033[48;2;" << blocks[i][j].r << ";" << blocks[i][j].g << ";" << blocks[i][j].b << "m";
                }
                cur = blocks[i][j];
            }
            ss << " ";
        }
        // before new line, reset if the color is not default.
        if (cur != defcolor) {
            ss << "\033[0m";
            cur = defcolor; // 这里不要忘记也重置自己记录的变量
        }
        ss << endl;
    }
    // clog << ss.str(); // 取消注释可以看实际控制台变色效果
    // 这里也容易忘记。必须输出大写。不足2位需要补前导0。
    cout << uppercase << hex << setfill('0');
    for (char &c: ss.str()) {
        cout << "\\x" << setw(2) << int(c);
    }
    cout << endl;
    return 0;
}