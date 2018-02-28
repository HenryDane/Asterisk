/* returns -3 if no such quest
   returns -2 if quest is waiting for action
   returns -1 if quest not assigned
   returns  0 if quest complete
   else returns pointer to next line of text
*/
int get_quest_line(int quest_id);

/* returns -2 if quest not assigned / non-existent / waiting / complete
   returns -1 if no visual update
   returns  0 if blank screen
   else returns bitmap id
*/
int get_quest_visual(int quest_id);

unsigned char get_quest_char_dat(unsigned int position);

void set_quest_char_dat(unsigned char dat, unsigned int position);
