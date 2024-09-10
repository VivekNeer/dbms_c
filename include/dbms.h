#ifndef DBMS_H
#define DBMS_H

void init_dbms();
void create_record(const char *record);
void read_record(const char *query);
void update_record(const char *query);
void delete_record(const char *query);

#endif // DBMS_H
