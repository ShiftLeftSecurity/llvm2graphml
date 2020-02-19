declare void @helloWorldExt(i32, i8, ...)

define void @helloWorld(i32, i32, i32*, i1) {
  ret void
}

declare void @llvm.memcpy.i8(i8*, i8*)