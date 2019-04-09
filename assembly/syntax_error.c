

/*

!1 Syntax error at token [TOKEN][004:003] ENDLINE - отсутствует имя 
?2 Syntax error at token [TOKEN][003:016] LABEL "l2:" - ".name "dsfdsf" l2:	sti	r1,%:live,%0"
*3 Syntax error at token [TOKEN][001:001] INSTRUCTION "name"
!4 Syntax error at token [TOKEN][003:003] ENDLINE - no comment
?5 Syntax error at token [TOKEN][003:001] LABEL "l2:" - no commetn at all, even .comment
*6 Syntax error - unexpected end of input (Perhaps you forgot to end with a newline ?)
!7 Syntax error at token [TOKEN][007:013] END "(null)" .comment "just a basic living prog
?8 and	r1%0,r1
!9 Syntax error at token [TOKEN][005:014] INSTRUCTION "r100" and	r1, %0, r100
10 l2	sti	r1,%:live,%0 - Syntax error at token [TOKEN][004:004] INSTRUCTION "sti"
11 Syntax error at token [TOKEN][006:006] ENDLINE 	and	
12 Syntax error at token [TOKEN][004:001] END "(null)" - если вообще нет текста


*/