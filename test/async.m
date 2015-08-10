#include <Foundation/Foundation.h>
#include <dispatch/dispatch.h>
#include <stdio.h>

@interface Hoge : NSObject
- (id)init;
@end

@implementation Hoge
- (id)init {
    __block int i = 100;
    dispatch_async(dispatch_get_main_queue(), ^{
        printf("hoge %d\n", i);
    });
    printf("fuga\n");
}
@end

int main(int argc, char* argv[]) {
    @autoreleasepool {
        Hoge *hoge = [[Hoge alloc] init];
        dispatch_main();
    }
}
