%0 = type opaque

define internal i32 @"\01-[Shape square]"(%0*, i8*) {
  %3 = alloca %0*, align 8
  %4 = alloca i8*, align 8
  store %0* %0, %0** %3, align 8
  store i8* %1, i8** %4, align 8
  ret i32 42
}