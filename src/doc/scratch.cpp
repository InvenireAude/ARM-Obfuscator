void  set_type(S::Half e_type){
	header.e_type = pConverter->convert(e_type);
}
void  set_machine(S::Half e_machine){
	header.e_machine = pConverter->convert(e_machine);
}
void  set_version(S::Word e_version){
	header.e_version = pConverter->convert(e_version);
}
void  set_entry(S::Addr e_entry){
	header.e_entry = pConverter->convert(e_entry);
}
void  	set_phoff(S::Off e_phoff){
	header.e_phoff = pConverter->convert(e_phoff);
}
void  	set_shoff(S::Off e_shoff){
	header.e_shoff = pConverter->convert(e_shoff);
}
void  set_flags(S::Word e_flags){
	header.e_flags = pConverter->convert(e_flags);
}
void  set_ehsize(S::Half e_ehsize){
	header.e_ehsize = pConverter->convert(e_ehsize);
}
void  set_phentsize(S::Half e_phentsize){
	header.e_phentsize = pConverter->convert(e_phentsize);
}
void  set_phnum(S::Half e_phnum){
	header.e_phnum = pConverter->convert(e_phnum);
}
void  set_shentsize(S::Half e_shentsize){
	header.e_shentsize = pConverter->convert(e_shentsize);
}
void  set_shnum(S::Half e_shnum){
	header.e_shnum = pConverter->convert(e_shnum);
}
void  set_shstrndx(S::Half e_shstrndx){
	header.e_shstrndx = pConverter->convert(e_shstrndx);
}