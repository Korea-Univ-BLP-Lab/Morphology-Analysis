/*****************************************************************************/
int print_result (FILE *fp, int num_syl, char ej[][3], 
                  char tag_sequence[][MAX_TAG_LEN], char spacing_tag[][MAX_TAG2_LEN]) {
  int i;

  char morph[1000][100] = {0,}; /* ���¼� */
  char tags[1000][50] = {0,};   /* ǰ�� */
  int num_morph;
  int ej_num = 1; /* ������ ��(��ȣ) */

  char prev_tag[50] = {0,};
  int morph_in_ej[1000] = {0,}; /* ���¼Ұ� �� ��° ������ �����ֳ�? */
  char tag_head;

  int start_time = 2;
  int end_time = num_syl+1;

  int tag_style;

  /* �ʱ�ȭ */
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

      /* ���� */
      if (ej[i][0] == FIL) strcat(morph[num_morph], &ej[i][1]);
      else strcat(morph[num_morph], ej[i]);

      /* �±� */
      strcpy(tags[num_morph], &tag_sequence[i][2]);
      morph_in_ej[num_morph] = ej_num;

      if (tag_style == E_STYLE) num_morph++;
      break;

    case 'B' :

      num_morph++; // ������

      /* ���� */
      if (ej[i][0] == FIL) strcat(morph[num_morph], &ej[i][1]);
      else strcat(morph[num_morph], ej[i]);

      /* �±� */
      strcpy(tags[num_morph], &tag_sequence[i][2]);
      morph_in_ej[num_morph] = ej_num;
      break;
    
    case 'I' :
      if (ej[i][0] == FIL) strcat(morph[num_morph], &ej[i][1]);
      else strcat(morph[num_morph], ej[i]);
      break;

    case 'E' :
      /* ���� */
      if (ej[i][0] == FIL) strcat(morph[num_morph], &ej[i][1]);
      else strcat(morph[num_morph], ej[i]);

      /* �±� */
      strcpy(tags[num_morph], &tag_sequence[i][2]);
      morph_in_ej[num_morph] = ej_num;

      num_morph++; // ������
      break;
    }

    if (strcmp(spacing_tag[i], "1") == 0) {
      ej_num++;
    }
  }

  if (tag_style == E_STYLE) num_morph--; // �ϳ� ���ҽ��Ѿ� ��

  {
    int prev = 1; /* ���� ���¼��� ���� ��ȣ */

    fprintf (fp, "%s/%s", morph[0], tags[0]);
    for (i = 1; i <= num_morph; i++) {
      if (morph_in_ej[i] != prev) 
        fprintf (fp, "\n%s/%s", morph[i], tags[i]); // �� �ѱ�
      else fprintf (fp, "+%s/%s", morph[i], tags[i]); // �̾ ��

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

  char morph[1000][100] = {0,}; /* ���¼� */
  char tags[1000][50] = {0,};   /* ǰ�� */
  int num_morph = -1;

  char prev_tag[50] = {0,};
  int ej_num = 1; /* ������ ��(��ȣ) */
  int morph_in_ej[1000]; /* ���¼Ұ� �� ��° ������ �����ֳ�? */
  char tag_head;

  int tag_style;

  int start_time = 2;
  int end_time = num_syl+1;

   /* �ʱ�ȭ */
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

      /* ���� */
      if (ej[i][0] == FIL) strcat(morph[num_morph], &ej[i][1]);
      else strcat(morph[num_morph], ej[i]);

      /* �±� */
      strcpy(tags[num_morph], &tag_sequence[i][2]);
      morph_in_ej[num_morph] = ej_num;

      if (tag_style == E_STYLE) num_morph++;
      break;

    case 'B' :

      num_morph++; // ������

      /* ���� */
      if (ej[i][0] == FIL) strcat(morph[num_morph], &ej[i][1]);
      else strcat(morph[num_morph], ej[i]);

      /* �±� */
      strcpy(tags[num_morph], &tag_sequence[i][2]);
      morph_in_ej[num_morph] = ej_num;
      break;
    
    case 'I' :
      if (ej[i][0] == FIL) strcat(morph[num_morph], &ej[i][1]);
      else strcat(morph[num_morph], ej[i]);
      break;

    case 'E' :
      /* ���� */
      if (ej[i][0] == FIL) strcat(morph[num_morph], &ej[i][1]);
      else strcat(morph[num_morph], ej[i]);

      /* �±� */
      strcpy(tags[num_morph], &tag_sequence[i][2]);
      morph_in_ej[num_morph] = ej_num;

      num_morph++; // ������
      break;
    } // end of switch

    if (strcmp(spacing_tag[i], "1") == 0) {
      ej_num++;
    }
  } // end of for

  if (tag_style == E_STYLE) num_morph--; // �ϳ� ���ҽ��Ѿ� ��

  {
    int prev = 1; /* ���� ���¼��� ���� ��ȣ */
    int print = 0;
    int cont = 0;

    for (i = 0; i <= num_morph; i++) {

      if (is_noun_tag(tags[i])) { /* ��� �±��̸� */

        /* ����� ���� ���ų�, �� ���� ���� ������ �ְ� �̾ ���� �� ������(��, ���ո��) */
        if (!print || (morph_in_ej[i] == prev && cont)) 
          fprintf (fp, "%s", morph[i]);
        else fprintf (fp, "\n%s", morph[i]); /* �ٸ� ������ �ְų� �̾ ���� �� ������ �ٹٲ� ��� */

        print = 1;
        cont = 1;
        prev = morph_in_ej[i];
      }
      else {/* ���� �±��̸� */
        if (is_nounsuffix_tag(tags[i])) /* ���̻� �±��̸� */
          cont = 1; /* �̾ ���� �� �ִ�. */
        else cont = 0;
      }
    }
    if (print) fprintf (fp, "\n");
  }

  return 1;
}

