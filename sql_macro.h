//
//  SqlMacro.h
//  lesschatcore-cocoa
//
//  Created by Frank Lin on 2/6/16.
//  Copyright © 2016 Frank Lin. All rights reserved.
//

#ifndef EASYSQLITE_SQL_MACRO_H_
#define EASYSQLITE_SQL_MACRO_H_

// namespace sql {}
#ifdef __cplusplus
#define NS_SQL_BEGIN                     namespace sql {
#define NS_SQL_END                       }
#define USING_NS_SQL                     using namespace sql
#else
#define NS_SQL_BEGIN
#define NS_SQL_END
#define USING_NS_SQL
#endif

#endif /* EASYSQLITE_SQL_MACRO_H_ */
