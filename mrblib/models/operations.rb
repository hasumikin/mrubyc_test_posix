class Operation

  def initialize
    @num = 0
    @str = ' ' # ' ' == 0x20(white space)
  end

  def fixnum_sample
    @num = w_FixnumAdd(@num)
    return @num
  end

  def string_sample
    @str = w_StringShift(@str)
    return '"' + @str + '"'
  end

  def array_sample
    ary = w_ArrayAsItIs([10001, 10002, 10003], 3)
    index = @num % 3
    return 'ary[' + index.to_s + '] : ' + ary[index].to_s
  end

end
