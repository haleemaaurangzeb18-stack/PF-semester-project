#include <QApplication>
#include <QMainWindow>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTableWidget>
#include <QMessageBox>
#include <cstring>

/* ================= CONSTANTS ================= */
#define max_stu 100
#define max_course 100
#define max_selectCourse 20
#define min_lim 5
#define max_lim 7

/* ================= STRUCTS ================= */
struct student {
    char name[20];
    int id;
    char major[20];
    int age;
    char email[30];
};

struct course {
    char code[10];
    char name[30];
    int credits;
};

struct SelectedCourse {
    int student_id;
    char course_code[max_selectCourse][10];
    int select_count;
};

/* ================= MAIN WINDOW ================= */
class MainWindow : public QMainWindow {
public:
    MainWindow() {
        resize(1000, 650);

        tabs = new QTabWidget(this);
        setCentralWidget(tabs);

        stu_count = 0;
        course_count = 0;

        for (int i = 0; i < max_stu; i++)
            Selected[i].select_count = 0;

        setupStudentTab();
        setupCourseTab();
        setupSelectTab();
        setupViewSelectedTab();
    }

private:
    QTabWidget *tabs;

    student students[max_stu];
    course courses[max_course];
    SelectedCourse Selected[max_stu];

    int stu_count;
    int course_count;

    /* ---------- STUDENT TAB ---------- */
    QLineEdit *sid, *sname, *sage, *semail;
    QComboBox *smajor;
    QTableWidget *stuTable;

    /* ---------- COURSE TAB ---------- */
    QLineEdit *ccode, *cname, *ccredit;
    QTableWidget *courseTable;

    /* ---------- SELECT TAB ---------- */
    QLineEdit *selSid, *selNum, *selCourseIdx;

    /* ---------- VIEW SELECTED ---------- */
    QTableWidget *selectedTable;

    /* ================= STUDENT TAB ================= */
    void setupStudentTab() {
        QWidget *w = new QWidget;
        QVBoxLayout *v = new QVBoxLayout;

        sid = new QLineEdit; sid->setPlaceholderText("Student ID");
        sname = new QLineEdit; sname->setPlaceholderText("Student Name");
        sage = new QLineEdit; sage->setPlaceholderText("Age");
        semail = new QLineEdit; semail->setPlaceholderText("Email");

        smajor = new QComboBox;
        smajor->addItems({"CY","DS","AI","CS","SE"});

        QPushButton *add = new QPushButton("Add Student");
        QPushButton *del = new QPushButton("Delete Student");

        connect(add, &QPushButton::clicked, this, [&] {
            if (stu_count >= max_stu) return;

            student s;
            s.id = sid->text().toInt();
            s.age = sage->text().toInt();

            strncpy(s.name, sname->text().toStdString().c_str(), sizeof(s.name)-1);
            strncpy(s.major, smajor->currentText().toStdString().c_str(), sizeof(s.major)-1);
            strncpy(s.email, semail->text().toStdString().c_str(), sizeof(s.email)-1);

            for (int i = 0; i < stu_count; i++)
                if (students[i].id == s.id) return;

            students[stu_count++] = s;
            refreshStudents();
        });

        connect(del, &QPushButton::clicked, this, [&] {
            int id = sid->text().toInt();
            for (int i = 0; i < stu_count; i++) {
                if (students[i].id == id) {
                    for (int j = i; j < stu_count-1; j++)
                        students[j] = students[j+1];
                    stu_count--;
                    refreshStudents();
                    refreshSelected();
                    return;
                }
            }
        });

        stuTable = new QTableWidget(0,5);
        stuTable->setHorizontalHeaderLabels({"ID","Name","Age","Major","Email"});

        v->addWidget(sid);
        v->addWidget(sname);
        v->addWidget(smajor);
        v->addWidget(sage);
        v->addWidget(semail);
        v->addWidget(add);
        v->addWidget(del);
        v->addWidget(stuTable);

        w->setLayout(v);
        tabs->addTab(w,"Students");
    }

    /* ================= COURSE TAB ================= */
    void setupCourseTab() {
        QWidget *w = new QWidget;
        QVBoxLayout *v = new QVBoxLayout;

        ccode = new QLineEdit; ccode->setPlaceholderText("Course Code");
        cname = new QLineEdit; cname->setPlaceholderText("Course Name");
        ccredit = new QLineEdit; ccredit->setPlaceholderText("Credit Hours");

        QPushButton *add = new QPushButton("Add Course");
        QPushButton *del = new QPushButton("Delete Course");

        connect(add, &QPushButton::clicked, this, [&] {
            if (course_count >= max_course) return;

            course c;
            c.credits = ccredit->text().toInt();
            strncpy(c.code, ccode->text().toStdString().c_str(), sizeof(c.code)-1);
            strncpy(c.name, cname->text().toStdString().c_str(), sizeof(c.name)-1);

            courses[course_count++] = c;
            refreshCourses();
        });

        connect(del, &QPushButton::clicked, this, [&] {
            QString code = ccode->text();
            for (int i = 0; i < course_count; i++) {
                if (code == courses[i].code) {
                    for (int j = i; j < course_count-1; j++)
                        courses[j] = courses[j+1];
                    course_count--;
                    refreshCourses();
                    refreshSelected();
                    return;
                }
            }
        });

        courseTable = new QTableWidget(0,3);
        courseTable->setHorizontalHeaderLabels({"Code","Course Name","Credits"});

        v->addWidget(ccode);
        v->addWidget(cname);
        v->addWidget(ccredit);
        v->addWidget(add);
        v->addWidget(del);
        v->addWidget(courseTable);

        w->setLayout(v);
        tabs->addTab(w,"Courses");
    }

    /* ================= SELECT COURSE TAB ================= */
    void setupSelectTab() {
        QWidget *w = new QWidget;
        QVBoxLayout *v = new QVBoxLayout;

        selSid = new QLineEdit; selSid->setPlaceholderText("Student ID");
        selNum = new QLineEdit; selNum->setPlaceholderText("How many courses");
        selCourseIdx = new QLineEdit; selCourseIdx->setPlaceholderText("Course index (1-based)");

        QPushButton *select = new QPushButton("Select Course");

        connect(select, &QPushButton::clicked, this, [&] {
            int id = selSid->text().toInt();
            int num = selNum->text().toInt();
            int idx = selCourseIdx->text().toInt() - 1;

            if (num < min_lim || num > max_lim) return;
            if (idx < 0 || idx >= course_count) return;

            int found = -1;
            for (int i = 0; i < stu_count; i++)
                if (students[i].id == id) found = i;

            if (found == -1) return;

            if (Selected[found].select_count >= max_selectCourse) return;

            strncpy(Selected[found].course_code[Selected[found].select_count],
                    courses[idx].code, 9);

            Selected[found].student_id = id;
            Selected[found].select_count++;

            refreshSelected();
        });

        v->addWidget(selSid);
        v->addWidget(selNum);
        v->addWidget(selCourseIdx);
        v->addWidget(select);

        w->setLayout(v);
        tabs->addTab(w,"Select Course");
    }

    /* ================= VIEW SELECTED ================= */
    void setupViewSelectedTab() {
        QWidget *w = new QWidget;
        QVBoxLayout *v = new QVBoxLayout;

        selectedTable = new QTableWidget(0,4);
        selectedTable->setHorizontalHeaderLabels(
            {"Student ID","Student Name","Course Code","Course Name"});

        v->addWidget(selectedTable);
        w->setLayout(v);

        tabs->addTab(w,"Selected Courses");
    }

    /* ================= REFRESH FUNCTIONS ================= */
    void refreshStudents() {
        stuTable->setRowCount(stu_count);
        for (int i = 0; i < stu_count; i++) {
            stuTable->setItem(i,0,new QTableWidgetItem(QString::number(students[i].id)));
            stuTable->setItem(i,1,new QTableWidgetItem(students[i].name));
            stuTable->setItem(i,2,new QTableWidgetItem(QString::number(students[i].age)));
            stuTable->setItem(i,3,new QTableWidgetItem(students[i].major));
            stuTable->setItem(i,4,new QTableWidgetItem(students[i].email));
        }
    }

    void refreshCourses() {
        courseTable->setRowCount(course_count);
        for (int i = 0; i < course_count; i++) {
            courseTable->setItem(i,0,new QTableWidgetItem(courses[i].code));
            courseTable->setItem(i,1,new QTableWidgetItem(courses[i].name));
            courseTable->setItem(i,2,new QTableWidgetItem(QString::number(courses[i].credits)));
        }
    }

    void refreshSelected() {
        selectedTable->setRowCount(0);

        for (int i = 0; i < stu_count; i++) {
            for (int j = 0; j < Selected[i].select_count; j++) {
                int row = selectedTable->rowCount();
                selectedTable->insertRow(row);

                selectedTable->setItem(row,0,new QTableWidgetItem(QString::number(students[i].id)));
                selectedTable->setItem(row,1,new QTableWidgetItem(students[i].name));
                selectedTable->setItem(row,2,new QTableWidgetItem(Selected[i].course_code[j]));

                for (int k = 0; k < course_count; k++)
                    if (strcmp(courses[k].code, Selected[i].course_code[j]) == 0)
                        selectedTable->setItem(row,3,new QTableWidgetItem(courses[k].name));
            }
        }
    }
};

/* ================= MAIN ================= */
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
