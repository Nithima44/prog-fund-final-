#include <stdio.h>
#include <string.h>

#define FILE_NAME "trips.csv"
#define MAX_LINE 256
#define MAX_TRIPS 100

// เช็กปี เพิ่มเติม
/*int is_leap_year(int year) {
    return ((year % 4 == 0 
}*/

// เช็กฟอแมทวันที่
int validate_date(const char *date) {
    int y, m, d;
    if (sscanf(date, "%d-%d-%d", &y, &m, &d) != 3) return 0;
    if (m < 1 || m > 12) return 0;

    int days_in_month[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    //if (is_leap_year(y)) days_in_month[2] = 29;
    if (d < 1 || d > days_in_month[m]) return 0;

    return 1; // valid
}

// เช็ก ID ซ้ำ
/*int is_trip_exist(const char *id) {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) return 0;

    
    }
    fclose(fp);
    return 0;
}*/


int open_file() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        fp = fopen(FILE_NAME, "w");
        if (fp == NULL) {
            printf("ไม่สามารถสร้างไฟล์ %s ได้\n", FILE_NAME);
            return -1;
        }
        fprintf(fp, "TripID,StartingPoint,Destination,TravelDate\n");
        fclose(fp);
        return 0;
    }

    fclose(fp);
    return 0;
}


int read_file() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("ไม่พบไฟล์ข้อมูล\n");
        return -1;
    }

    char line[MAX_LINE];
    printf("\n=== ข้อมูลการเดินทาง ===\n");
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
    fclose(fp);
    return 0;
}


int add_trip() {
    FILE *fp = fopen(FILE_NAME, "a");
    if (fp == NULL) {
        printf("ไม่สามารถเปิดไฟล์เพื่อเขียนได้\n");
        return -1;
    }

    char id[20], start[50], dest[50], date[20];
    printf("กรอก TripID (เช่น T016): ");
    scanf("%s", id);

    /*if (is_trip_exist(id)) {
        printf("TripID %s มีอยู่แล้ว \n", id);
        fclose(fp);
        return 1;  
    }*/

    printf("กรอกจุดเริ่มต้น: ");
    scanf("%s", start);
    printf("กรอกจุดหมายปลายทาง: ");
    scanf("%s", dest);

    do {
        printf("กรอกวันที่เดินทาง (YYYY-MM-DD): ");
        scanf("%s", date);
        if (!validate_date(date)) {
            printf(" วันที่ไม่ถูกต้องตามรูปแบบ กรุณาลองใหม่\n");
        }
    } while (!validate_date(date));

    fprintf(fp, "%s,%s,%s,%s\n", id, start, dest, date);
    fclose(fp);

    printf("เพิ่มข้อมูลเรียบร้อย\n");
    return 0;
}


int search_trip() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("ไม่พบไฟล์ข้อมูล\n");
        return -1;
    }

    char keyword[50];
    printf("ค้นหาจาก TripID หรือ Destination: ");
    scanf("%s", keyword);

    char line[MAX_LINE];
    int found = 0;
    fgets(line, sizeof(line), fp); 
    while (fgets(line, sizeof(line), fp)) {
        char id[20], start[50], dest[50], date[20];
        sscanf(line, "%[^,],%[^,],%[^,],%s", id, start, dest, date);
        if (strcmp(id, keyword) == 0 || strcmp(dest, keyword) == 0) {
            printf("%s", line);
            found = 1;
        }
    }
    fclose(fp);

    if (!found) {
        printf("ไม่พบข้อมูล\n");
        return 1;
    }
    return 0;
}


/*int update_trip() {
    char id[20];
    printf("กรอก TripID ที่ต้องการแก้ไข: ");
    scanf("%s", id);

    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("ไม่สามารถเปิดไฟล์เพื่ออ่านได้\n");
        return -1;
    }

    char lines[100][200];   
    int line_count = 0;
    int found = 0;

    while (fgets(lines[line_count], sizeof(lines[line_count]), fp)) {
        char tid[20], start[50], dest[50], date[20];
        if (sscanf(lines[line_count], ************
                   tid, start, dest, date) == 4) {
            if (strcmp(tid, id) == 0) {
                found = 1;
                char new_start[50], new_dest[50], new_date[20];

                printf("กรอกจุดเริ่มต้นใหม่ (เดิม: %s): ", start);
                scanf("%s", new_start);

                printf("กรอกจุดหมายปลายทางใหม่ (เดิม: %s): ", dest);
                scanf("%s", new_dest);
                ***************

                do {
                    printf("กรอกวันที่เดินทางใหม่ (เดิม: %s, YYYY-MM-DD): ", date);
                    scanf("%s", new_date);
                    if (!validate_date(new_date)) {
                        printf("วันที่ไม่ถูกต้องตามรูปแบบ กรุณาลองใหม่\n");
                *************
            }
        }
        line_count++;
    }
    fclose(fp);

    if (!found) {
        printf("ไม่พบ TripID %s\n", id);
        return 1;
    }

    fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        printf("ไม่สามารถเขียนไฟล์ %s ได้\n", FILE_NAME);
        return -1;
    }
    for (int i = 0; i < line_count; i++) {
        fputs(lines[i], fp);
    }
    fclose(fp);

    printf("แก้ไขข้อมูลเรียบร้อย\n");
    return 0;
}*/


int delete_trip() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("ไม่พบไฟล์ข้อมูล\n");
        return -1;
    }

    char lines[MAX_TRIPS][MAX_LINE];
    int count = 0;
    while (fgets(lines[count], sizeof(lines[count]), fp)) {
        count++;
    }
    fclose(fp);

    char target[20];
    printf("กรอก TripID ที่ต้องการลบ: ");
    scanf("%s", target);

    int found = 0;
    fp = fopen(FILE_NAME, "w");
    if (fp == NULL) return -1;
    for (int i = 0; i < count; i++) {
        if (i == 0) {
            fputs(lines[i], fp); 
            continue;
        }
        char id[20];
        sscanf(lines[i], "%[^,],", id);
        if (strcmp(id, target) == 0) {
            found = 1;
            continue; 
        }
        fputs(lines[i], fp);
    }
    fclose(fp);

    if (found) {
        printf(" ลบข้อมูลเรียบร้อยแล้ว\n");
        return 0;
    } else {
        printf(" ไม่พบ TripID นี้\n");
        return 1;
    }
}


int display_menu() {
    int choice;
    do {
        printf("\n=== เมนูจัดการข้อมูลการเดินทาง ===\n");
        printf("1. แสดงข้อมูลทั้งหมด\n");
        printf("2. เพิ่มข้อมูล\n");
        printf("3. ค้นหาข้อมูล (TripID/Destination)\n");
        printf("4. แก้ไขข้อมูล\n");
        printf("5. ลบข้อมูล\n");
        printf("6. ออกจากโปรแกรม\n");
        printf("เลือกเมนู (1-6): ");
        scanf("%d", &choice);

        int result;
        switch (choice) {
            case 1: result = read_file(); break;
            case 2: result = add_trip(); break;
            case 3: result = search_trip(); break;
            //case 4: result = update_trip(); break;
            case 5: result = delete_trip(); break;
            case 6: printf("ออกจากโปรแกรมแล้ว\n"); return 0;
            default: printf("เลือกเมนูไม่ถูกต้อง\n"); result = 1;
        }

        if (result == -1) printf("เกิดข้อผิดพลาด\n");

    } while (choice != 6);
    return 0;
}


int main() {
    if (open_file() == -1) return -1;
    return display_menu();
}
