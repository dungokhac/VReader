void EnQueue(String s){ // them vao hang doi
	//xong

	if(hang_doi_sothietbidangdoi == hang_doi_tong){
		//dua ra thong bao len man hinh
		thong_bao_udp("TBC001");
		return;
	}else{
		// logloi(" trong danh sach "+iin_aray(s));
		if(!in_array(s) ){
			hang_doi[hang_doi_rear] = s;
			hang_doi_rear = (hang_doi_rear + 1) % hang_doi_tong;
			hang_doi_sothietbidangdoi = hang_doi_sothietbidangdoi + 1;
			hang_doi_sothietbidangdoi2 = hang_doi_sothietbidangdoi2 + 1;
		}
	}
	if(hangdoi_Front() == s){
		udp_time = 0;

		thong_bao_udp("TBC002");
	}else if(vitrihangdoi(s) >= 1){

		thong_bao_udp("TBC003_1");
	}
	// serial_out();
}
void DeQueue(String s){ // xoa khỏi hàng đợi
	//chua xong
		
	if(in_array(s)){
		udp_out_ip("106TBC005", hangdoi_Front());
		if(hangdoi_Front() == s){

			hang_doi[hang_doi_front] = "";
			hang_doi_front = (hang_doi_front + 1) % hang_doi_tong;
			hang_doi_sothietbidangdoi = hang_doi_sothietbidangdoi - 1;
			hang_doi_sothietbidangdoi2 = hang_doi_sothietbidangdoi2 - 1;
			str_lenhtbngoai="";
			//ngat ket noi huy lenh udp
		}else{
			xoaiptrongdanhsach(s);
		}

	}
	if( hang_doi_sothietbidangdoi <= 0 ){
		// thong_bao_udp("TBC004");
		hang_doi_sothietbidangdoi = 0;
	}
}
bool hangdoi_IsEmpty(){
 	return (hang_doi_sothietbidangdoi == 0);
}
String hangdoi_Front(){ // lay vi tri hien tai 
	//xong
	int len=0;
	while(hang_doi[hang_doi_front] == "" && len <= hang_doi_tong){
	    hang_doi_front = (hang_doi_front + 1) % hang_doi_tong;
		hang_doi_sothietbidangdoi = hang_doi_sothietbidangdoi - 1;
		len++;
	}
	return  hang_doi[hang_doi_front];
}
int hangdoi_Size() {// so luong thiet bi dang cho ket noi
	//xong
    return hang_doi_sothietbidangdoi;
}
bool in_array(String s){ // kiem tra ip da co trong danh sach chưa
	int a1=hang_doi_rear,a2=hang_doi_front,a3=hang_doi_sothietbidangdoi,i=0,b=0;
	for(i = 0; i < a3; i++)
	{
		b = a2 % hang_doi_tong;
		if(s.equals(hang_doi[b])) return true;
		a2++;
	}
	return false;
}

int vitrihangdoi(String s){ // kiem tra xem ip dang o vi tri bao nhieu
	int a1=hang_doi_rear,a2=hang_doi_front,a3=hang_doi_sothietbidangdoi,i=0,b=0,vitri=0;
	for(i = 0; i < a3; i++)
	{
		b = a2 % hang_doi_tong;
		if(s.equals(hang_doi[b])){
			return vitri;
		}
		if(b == a1){
			return -1;
		}
		a2++;
		if(hang_doi[b].length() != 0){
			vitri++;
		}	
	}
}
void danhsachip(){
	int a1=hang_doi_rear,a2=hang_doi_front,a3=hang_doi_sothietbidangdoi,i=0,b=0,c=0;
	for(i = 0; i < a3; i++)
	{
		String iip = hang_doi[a2 % hang_doi_tong];
		if( iip != ""){
			// add_to_serial(str_idtb(my_id)+"^104"+String(c)+"");
			// serial_out();
	      	guivitrihangcho(str_idtb(my_id)+"^104"+String(c)+"",iip);
	      	// guivitrihangcho("A","hang_doi[b]");
		}
		c++;
		a2++;
	}
}

void logloi(String s){
// 	add_to_serial("|"+s+"|");
// 	serial_out();	
}
void xoaiptrongdanhsach(String s)
{
	int a1=hang_doi_rear,a2=hang_doi_front,a3=hang_doi_sothietbidangdoi,i=0,b=0;
	for(i = 0; i < a3; i++)
	{
		b = a2 % hang_doi_tong;
		if(s.equals(hang_doi[b])) hang_doi[b] ="";
		a2++;
	}
}
void guivitrihangcho(String s,String ip){
	// udp_out_ip(str_idtb(my_id)+"^104"+s,ip);
}