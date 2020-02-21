define i32 @abs(i32 %x) {
entry:
  %tmp = alloca i32
  %cmp = icmp slt i32 %x, 0
  br i1 %cmp, label %then, label %else

then:
  %tmpSub = sub nsw i32 0, %x
  store i32 %tmpSub, i32* %tmp
  br label %end

else:
  store i32 %x, i32* %tmp
  br label %end

end:
  %rval = load i32, i32* %tmp
  ret i32 %rval
}
