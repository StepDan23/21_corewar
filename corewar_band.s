.name "outstanding project"
.comment "125%"

begin:
st r1, 6
live            %66
ld              %4,r2
sub             r2,r2,r2
st              r2, -100
live            %1
fork            %-511
st r1, -5
fork            %-511
st r1, -5
fork            %-511
st r1, -5
zjmp %:begin
