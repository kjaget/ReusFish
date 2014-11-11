
while ($line = <>)
{
   if ($line =~ /source name = \"([^"]+)\" level = \"(\d)\"/)
   {
      @names = split (/ /, $1);
      $prefix = "";
      if (($names[0] eq "Great") || ($names[0] eq "Superior"))
      {
	 $prefix = $names[0] . "_";
	 shift @names;
      }
      
      print "m_source_list.Register(";
      $type = join "_", @names;
      $type =~ tr/a-z/A-Z/;
      print $type;
      print ", ";
      print $2;
      print ", SourceBuilder<$prefix";
      print join '',@names;
      printf ">);\n";
   }
   elsif ($line =~ /source name = \"([^"]+)\"/)
   {
      @names = split (/ /, $1);
      $prefix = "";
      if (($names[0] eq "Great") || ($names[0] eq "Superior"))
      {
	 $prefix = $names[0] . "_";
	 shift @names;
      }
      
      print "m_source_list.Register(";
      $type = join "_", @names;
      $type =~ tr/a-z/A-Z/;
      print $type;
      print ", x, SourceBuilder<$prefix";
      print join '',@names;
      printf ">);\n";
   }
}
