/*
 * infoelement.h
 *
 *  Created on: 21-10-2016
 *      Author: wawrzyniakw
 */

#ifndef INFOELEMENT_H_
#define INFOELEMENT_H_


class InfoElement {
public:
	char* info; // information
	int time; // time_to_show

	int getTime();

	InfoElement(char *tinfo, int ttime);

	InfoElement();

	InfoElement(const InfoElement &obj);
};

#endif /* INFOELEMENT_H_ */
