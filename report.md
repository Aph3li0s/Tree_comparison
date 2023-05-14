# Báo cáo thực nghiệm so sánh cây

Họ và tên: Phan Huỳnh Ngọc Trâm

MSSV: 22521500

Mail: 22521500@gm.uit.edu.vn

Link Github báo cáo: https://github.com/Aph3li0s/

## I. Mở đầu

* *AVL Tree* và *RB Tree* là ví dụ tiêu biểu trong cấu trúc cây được cải tiến từ cây nhị phân tìm kiếm BST và đóng vai trò quan trọng trong việc xây dựng và quản lý dữ liệu. Vì vậy, để có thể đưa ra những đánh giá khách quan, ta cần thực hiện thực nghiệm so sánh giữa hai cây. 
* Vì cả hai cây đều được kế thừa từ BST, chúng đều có tối đa 2 child trong mỗi node. Vì vậy, chiều cao bé nhất của cả hai cây sẽ bằng $h_{min} = floor(log(n))$
* Đối với cây AVL, chiều cao lớn nhất là $floor(h_{max} = 1.44log_2(n))$
* Đối với cây RB, chiều cao lớn nhất là $floor(h_{max} = 2log_2(n))$

## II. Chuẩn bị và tiến hành
**Input**: Bao gồm 10 bộ dữ liệu gồm các số nguyên dương có giá trị trong khoảng $[0, 10^6]$, bộ đầu tiên chứa các giá trị giảm dần, bộ thứ hai chứa các giá trị tăng dần. Các bộ còn lại chứa các giá trị ngẫu nhiên


**Output**: Độ dài của cây AVL và cây RB


**Quy trình:**
* **B1:** Chạy file random để sinh ra các giá trị ngẫu nhiên cho 10 test cases.
* **B2:** Lần lượt chạy cây AVL và cây RB để tìm ra chiều cao cây sau mỗi test case, sau đó lưu các giá trị vào file .txt output
* **B3** Lặp lại quy trình 10 lần (tức là mỗi test case ta sẽ random 10 lần và chạy 10 lần)
* **B4** Lưu các giá trị vào mảng, tìm trung vị của mỗi kết quả thuộc từng bộ test case, sau đó vẽ biểu đồ so sánh

## III. Kết quả và đánh giá
*Chi tiết: https://github.com/Aph3li0s/Tree_comparison/blob/main/demo.ipynb)*
![](https://hackmd.io/_uploads/S12x4b0V2.png)


* Nhìn chung, chiều cao lớn nhất của cây đều không vượt quá giới hạn cận trên và cận dưới của chúng. 
* Khi insert các giá trị vào cây, cây RB giữ được độ ổn định về chiều cao khá tốt khi độ dài xấp xỉ 24, cây AVL có sự dao động giữa 23 và 24. Cây RB cần chiều cao lớn hơn để có thể cân bằng trong điều kiện ràng buộc giữa nút đen và đỏ. 
* Đối với những bộ data mà cây AVL cần ít chiều cao để lưu trữ, cây RB lại cần chiều cao khá sát với cận trên của nó, thể hiện độ tương phản rõ rệt.