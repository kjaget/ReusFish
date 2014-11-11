my $base = "";
my $name = "";

my $source_dep = "";
my $aspect_dep1 = "";
my $aspect_dep2 = "";

@aspect_level = ("", "Lesser_", "Potent_", "Greater_", "Sublime_");

while ($line = <>)
{
   if ($line =~ / Plants -->/)
   {
      $base = "Plant";
   }
   elsif ($line =~ / Animals -->/)
   {
      $base = "Animal";
   }
   elsif ($line =~ / Minerals -->/)
   {
      $base = "Mineral";
   }
   elsif ($line =~ /source name = \"([^"]+)\"/)
   {
      @names = split (/ /, $1);
      if (($names[0] eq "Great") || ($names[0] eq "Superior"))
      {
	 $prefix = shift @names;
      }
      else
      {
	 $prefix = "";
	 push @names_in_order, join(" ", @names);
	 $name = join("_", @names);
	 $name =~ tr/a-z/A-Z/;
      }
      $best_prefix{join(" ", @names)} = $prefix;
      $base{join(" ", @names)} = $base;
   }
   elsif (($line =~ /<\/and>/) ||
          ($line =~ /<\/source>/) )
   {
      if (($name ne "") && ($source_dep ne "") && ($aspect_dep1 ne ""))
      {
      print "N:$name S:$source_dep A:$aspect_dep1 A:$aspect_dep2\n";
	 $upgrades{$source_dep} .= ";" if (defined $upgrades{$source_dep});
	 $upgrades{$source_dep} .= $name;
	 $upgrades{$source_dep} .= ", Aspects::".$aspect_dep1;
	 $upgrades{$source_dep} .= ", Aspects::".$aspect_dep2 if ($aspect_dep2 ne "");

      }

      $name = "" if ($line =~ /<\/source>/);
      $source_dep = "" if ($line =~ /<\/source>/);
      $aspect_dep1 = "";
      $aspect_dep2 = "";
   }
   elsif ($line =~ /sourceDependency source = \"([^"]+)\"/)
   {
      @names = split (/ /, $1);
      if (($names[0] eq "Great") || ($names[0] eq "Superior"))
      {
	 $prefix = shift @names;
      }
      $source_dep = join('', @names);
   }
   elsif ($line =~ /aspectDependency aspect = \"([^"]+)\" level = \"(\d)\"/)
   {
      $aspect_name = $aspect_level[$2] . $1;
      $aspect_name =~ tr/a-z/A-Z/;
      if ($aspect_dep1 eq "")
      {
	 $aspect_dep1 = $aspect_name;
      }
      else
      {
	 $aspect_dep2 = $aspect_name;
      }
   }

}

@prefix_names = ("", "Great", "Superior");
@source_names = ("Plant", "Animal", "Mineral");
foreach $source_type (@source_names)
{
   for ($i = 0 ; $i <= $#names_in_order; $i++)
   {
      $name = $names_in_order[$i];
      next if ($base{$name} ne $source_type);

      $level = 3 if ($best_prefix{$name} eq "");
      $level = 2 if ($best_prefix{$name} eq "Great");
      $level = 1 if ($best_prefix{$name} eq "Superior");

      $base_class = $source_type;
      for ($j = $level - 1; $j < 3; $j++)
      {
	 $class_name = $prefix_names[$j - $level + 1];
	 $class_name .= "_" if ($class_name ne "");
	 @names = split(/ /, $name);
	 $class_name .= join('', @names);

	 print "class $class_name : public $base_class\n";
	 print "{\n   public:\n      $class_name()\n      {\n         Create();\n      }\n\n";
	 print "      $class_name(const std::vector<Aspects::aspect_t> aspects)\n      {\n         Create();\n         m_aspects = aspects;\n      }\n\n";
	 print "      void Create(void)\n      {\n";
	 print "         m_name = \"";
	 print $prefix_names[$j - $level + 1];
	 print " " if ($prefix_names[$j - $level + 1] ne "");
	 print "$name\";\n";
	 if ($j == ($level - 1))
	 {
	    $type = join "_", @names;
	    $type =~ tr/a-z/A-Z/;
	    print "         m_type = $type;\n";
	 }
	 print "         m_level = ";
	 print $j + 1;
	 print ";\n";
	 print "         AddUpgrades();\n" if ($j == ($level - 1));
	 print "      }\n\n";
	 if ($j == ($level - 1))
	 {
	    print "      void AddUpgrades(void)\n      {\n";
	    print "         m_upgrades.clear();\n";

	    @upgrades = split /;/, $upgrades{join('', @names)};
	    foreach $upgrade (@upgrades)
	    {
	       print "         AddUpgrade($upgrade);\n";
	    }

	    print "      }\n\n";
	    if ($level != 3)
	    {
	       print "      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_dummy);\n" ;
	       print "      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield, unsigned m_natura_adder);\n" if ($base_class eq "Plant");
	    }
	 }
	 print "      void GetYield(std::vector<Space> &spaces, unsigned loc, Yield &yield)";
	 if ($level == 3)
	 {
	    print ";\n";
	 }
	 else
	 {
	    print "\n      {\n         ";
	    print $base_class . "::" if ($j != ($level - 1));
	    print "GetYield(spaces, loc, yield, foo);\n";
	    print "      }\n";
	 }
	 if ($source_type eq "Plant")
	 {
	    print "      void GetNatura(std::vector<Space> &spaces, unsigned loc, Yield &yield)";
	    if ($level == 3)
	    {
	       print ";\n";
	    }
	    else
	    {
	       print "\n      {\n         ";
	       print $base_class . "::" if ($j != ($level - 1));
	       print "GetNatura(spaces, loc, yield, foo);\n";
	       print "      }\n";
	    }
	 }
	 print "      $class_name* Clone() const {return new $class_name\(*this);}\n";
	 print "};\n\n";

	 if ($j == ($level - 1))
	 {
	    $base_class = $class_name;
	 }
      }
   }
}


