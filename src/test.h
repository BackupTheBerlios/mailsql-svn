/* xmlparser.c */
int parse_db(xmlDocPtr doc, xmlNodePtr cur, struct config *conf_struct);
struct config *xmlparse(char *filename);
int freeconf(struct config *conf);
int main(int argc, char **argv);
