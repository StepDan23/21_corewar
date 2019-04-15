
#dsgdsg

.name #COMMENT 



"dsfdsf"


.comment "just a basic living prog"

l2:
	sti	r1, %:live, %0
	and	r1, %0, r1 #COMMENT

live:
	live	%1
	zjmp	%:live
