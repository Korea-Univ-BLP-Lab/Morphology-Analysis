/*****************************************************************************/
int print_result (FILE *fp, int num_syl, char ej[][3], 
                  char tag_sequence[][MAX_TAG_LEN], char spacing_tag[][MAX_TAG2_LEN]) {
  int i;

  char morph[1000][100] = {0,}; /* 형태소 */
  char tags[1000][50] = {0,};   /* 품사 */
  int num_morph;
  int ej_num = 1; /* 어절의 수(번호) */

  char prev_tag[50] = {0,};
  int morph_in_ej[1000] = {0,}; /* 형태소가 몇 번째 어절에 속해있나? */
  char tag_head;

  int start_time = 2;
  int end_time = num_syl+1;

  int tag_style;

  /* 초기화 */
  i = start_time;
  while (1) {
    if (tag_sequence[i][0] == 'B') {
      num_morph = -1;
      tag_style = B_STYLE;
      break;
    }
    else if (tag_sequence[i][0] == 'I') {
      num_morph = 0;
      tag_style = E_STYLE;
      break;
    }
    i++;
  }

  for (i = start_time; i <= end_time; i++) {
    tag_head = tag_sequence[i][0];

    switch (tag_head) {

    case 'S' :

      if (tag_style == B_STYLE) num_morph++;

      /* 음절 */
      if (ej[i][0] == FIL) strcat(morph[num_morph], &ej[i][1]);
      else strcat(morph[num_morph], ej[i]);

      /* 태그 */
      strcpy(tags[num_morph], &tag_sequence[i][2]);
      morph_in_ej[num_morph] = ej_num;

      if (tag_style == E_STYLE) num_morph++;
      break;

    case 'B' :

      num_morph++; // 선증가

      /* 음절 */
      if (ej[i][0] == FIL) strcat(morph[num_morph], &ej[i][1]);
      else strcat(morph[num_morph], ej[i]);

      /* 태그 */
      strcpy(tags[num_morph], &tag_sequence[i][2]);
      morph_in_ej[num_morph] = ej_num;
      break;
    
    case 'I' :
      if (ej[i][0] == FIL) strcat(morph[num_morph], &ej[i][1]);
      else strcat(morph[num_morph], ej[i]);
      break;

    case 'E' :
      /* 음절 */
      if (ej[i][0] == FIL) strcat(morph[num_morph], &ej[i][1]);
      else strcat(morph[num_morph], ej[i]);

      /* 태그 */
      strcpy(tags[num_morph], &tag_sequence[i][2]);
      morph_in_ej[num_morph] = ej_num;

      num_morph++; // 후증가
      break;
    }

    if (strcmp(spacing_tag[i], "1") == 0) {
      ej_num++;
    }
  }

  if (tag_style == E_STYLE) num_morph--; // 하나 감소시켜야 함

  {
    int prev = 1; /* 이전 형태소의 어절 번호 */

    fprintf (fp, "%s/%s", morph[0], tags[0]);
    for (i = 1; i <= num_morph; i++) {
      if (morph_in_ej[i] != prev) 
        fprintf (fp, "\n%s/%s", morph[i], tags[i]); // 줄 넘김
      else fprintf (fp, "+%s/%s", morph[i], tags[i]); // 이어서 씀

      prev = morph_in_ej[i];
    }

    fprintf (fp, "\n\n");
  }
  return 1;
}

/*****************************************************************************/
int print_noun_result (FILE *fp, int num_syl, char ej[][MAX_WORD_LEN], 
                       char tag_sequence[][MAX_TAG_LEN], char spacing_tag[][MAX_TAG2_LEN]) {
  int i;

  char morph[1000][100] = {0,}; /* 형태소 */
  char tags[1000][50] = {0,};   /* 품사 */
  int num_morph = -1;

  char prev_tag[50] = {0,};
  int ej_num = 1; /* 어절의 수(번호) */
  int morph_in_ej[1000]; /* 형태소가 몇 번째 어절에 속해있나? */
  char tag_head;

  int tag_style;

  int start_time = 2;
  int end_time = num_syl+1;

   /* 초기화 */
  i = start_time;
  while (1) {
    if (tag_sequence[i][0] == 'B') {
      num_morph = -1;
      tag_style = B_STYLE;
      break;
    }
    else if (tag_sequence[i][0] == 'I') {
      num_morph = 0;
      tag_style = E_STYLE;
      break;
    }
    i++;
  }

  for (i = start_time; i <= end_time; i++) {
    tag_head = tag_sequence[i][0];

    switch (tag_head) {

    case 'S' :

      if (tag_style == B_STYLE) num_morph++;

      /* 음절 */
      if (ej[i][0] == FIL) strcat(morph[num_morph], &ej[i][1]);
      else strcat(morph[num_morph], ej[i]);

      /* 태그 */
      strcpy(tags[num_morph], &tag_sequence[i][2]);
      morph_in_ej[num_morph] = ej_num;

      if (tag_style == E_STYLE) num_morph++;
      break;

    case 'B' :

      num_morph++; // 선증가

      /* 음절 */
      if (ej[i][0] == FIL) strcat(morph[num_morph], &ej[i][1]);
      else strcat(morph[num_morph], ej[i]);

      /* 태그 */
      strcpy(tags[num_morph], &tag_sequence[i][2]);
      morph_in_ej[num_morph] = ej_num;
      break;
    
    case 'I' :
      if (ej[i][0] == FIL) strcat(morph[num_morph], &ej[i][1]);
      else strcat(morph[num_morph], ej[i]);
      break;

    case 'E' :
      /* 음절 */
      if (ej[i][0] == FIL) strcat(morph[num_morph], &ej[i][1]);
      else strcat(morph[num_morph], ej[i]);

      /* 태그 */
      strcpy(tags[num_morph], &tag_sequence[i][2]);
      morph_in_ej[num_morph] = ej_num;

      num_morph++; // 후증가
      break;
    } // end of switch

    if (strcmp(spacing_tag[i], "1") == 0) {
      ej_num++;
    }
  } // end of for

  if (tag_style == E_STYLE) num_morph--; // 하나 감소시켜야 함

  {
    int prev = 1; /* 이전 형태소의 어절 번호 */
    int print = 0;
    int cont = 0;

    for (i = 0; i <= num_morph; i++) {

      if (is_noun_tag(tags[i])) { /* 명사 태그이면 */

        /* 출력한 적이 없거나, 앞 명사와 같은 어절에 있고 이어서 찍을 수 있으면(예, 복합명사) */
        if (!print || (morph_in_ej[i] == prev && cont)) 
          fprintf (fp, "%s", morph[i]);
        else fprintf (fp, "\n%s", morph[i]); /* 다른 어절에 있거나 이어서 찍을 수 없으면 줄바꿔 출력 */

        print = 1;
        cont = 1;
        prev = morph_in_ej[i];
      }
      else {/* 비명사 태그이면 */
        if (is_nounsuffix_tag(tags[i])) /* 접미사 태그이면 */
          cont = 1; /* 이어서 찍을 수 있다. */
        else cont = 0;
      }
    }
    if (print) fprintf (fp, "\n");
  }

  return 1;
}

